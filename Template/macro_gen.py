import os
import re
import subprocess
from copy import deepcopy


def generate_dep_lines(dep_from, dep_tos):
    return (
        (["#ifdef " + dep_from] if dep_from else [])
        + ["#define " + dep_to for dep_to in sorted(dep_tos)]
        + (["#endif"] if dep_from else [])
    )


def generate_include_lines(dep, includes):
    return (
        ["#ifdef " + dep]
        + sorted(['#include "{}"'.format(include) for include in includes])
        + ["#endif"]
    )


def write_macro_file(macro_filepath, lines):
    try:
        with open(macro_filepath, "r") as macro_file:
            original_lines = macro_file.readlines()
    except FileNotFoundError:
        original_lines = []
    file = open(macro_filepath, "w")
    file.write("\n".join(lines))
    file.close()
    subprocess.Popen(["clang-format", "-i", macro_filepath]).wait()
    with open(macro_filepath, "r") as macro_file:
        new_lines = macro_file.readlines()
    if original_lines != new_lines:
        print("{} updated.".format(macro_filepath))


MACRO_GEN_PATTERN = re.compile(r"^.*// !macro_gen$")
ALL_DECLARE_PATTERN = re.compile(r"^.*// ALL ([A-Z0-9_]+)$")
ALL_DEPS_PATTERN = re.compile(r"^.*// \^ ([A-Z0-9_]+)$")
ALL_DEPS_SHORT_PATTERN = re.compile(r"^#ifdef ([A-Z0-9_]+) // \^$")
DEPS_PATTERN = re.compile(r"^.*//\s*([A-Z0-9_]+) => ([A-Z0-9_]+)\s*$")
GLOBAL_DEPS_PATTERN = re.compile(r"^.*//\s* => ([A-Z0-9_]+)\s*$")
INCLUDE_PATTERN = re.compile(r"^.*//\s*([A-Z0-9_]+) => INCLUDE (\S+)\s*$")
GLOBAL_INCLUDE_PATTERN = re.compile(r"^(#include \S+)\s*// INCLUDE$")


class TemplateConfigs:
    def __init__(self):
        self.should_macro_gen = False
        self.all_dep = ""
        self.deps = {}
        self.all_deps = set()
        self.global_deps = set()
        self.includes = {}
        self.global_includes = set()

    def handle_line(self, line):
        match = MACRO_GEN_PATTERN.match(line)
        if match:
            self.should_macro_gen = True
            return
        match = ALL_DECLARE_PATTERN.match(line)
        if match:
            self.all_dep = match[1]
            return
        match = INCLUDE_PATTERN.match(line)
        if match:
            dep = match[1]
            include = match[2]
            if dep not in self.includes:
                self.includes[dep] = set()
            self.includes[dep].add(include)
            return
        match = GLOBAL_INCLUDE_PATTERN.match(line)
        if match:
            self.global_includes.add(match[1])
            return
        match = ALL_DEPS_PATTERN.match(line)
        if match:
            self.all_deps.add(match[1])
            return
        match = ALL_DEPS_SHORT_PATTERN.match(line)
        if match:
            self.all_deps.add(match[1])
            return
        match = GLOBAL_DEPS_PATTERN.match(line)
        if match:
            self.global_deps.add(match[1])
            return
        match = DEPS_PATTERN.match(line)
        if match:
            dep_from = match[1]
            dep_to = match[2]
            if dep_from not in self.deps:
                self.deps[dep_from] = set()
            self.deps[dep_from].add(dep_to)


def handle(template_filepath):
    configs = TemplateConfigs()
    # Load all_deps and deps
    with open(template_filepath, "r") as template_file:
        for line in template_file.readlines():
            configs.handle_line(line)
    if not configs.should_macro_gen:
        return
    # Propagage deps
    while True:
        new_deps = deepcopy(configs.deps)
        for dep_from, dep_tos in configs.deps.items():
            for dep_to in dep_tos:
                new_deps[dep_from] |= configs.deps.get(dep_to, set())
        if configs.deps == new_deps:
            break
        configs.deps = new_deps
    # Generate codes
    lines = generate_dep_lines(configs.all_dep, configs.all_deps)
    if lines:
        lines.append("")
    lines.extend(generate_dep_lines("", configs.global_deps))
    for dep_from, dep_tos in sorted(configs.deps.items()):
        if lines:
            lines.append("")
        lines.extend(generate_dep_lines(dep_from, dep_tos))
    for dep, include in sorted(configs.includes.items()):
        if lines:
            lines.append("")
        lines.extend(generate_include_lines(dep, include))
    if lines:
        lines.append("")
    lines.extend(sorted(configs.global_includes))
    if lines and lines[-1]:
        lines.append("")
    # Write file
    macro_filepath = re.sub(".h$", "_macros.h", template_filepath)
    write_macro_file(macro_filepath, lines)


for subdir, dirs, files in os.walk(os.path.join(os.environ["ICPC_HOME"], "Template")):
    for filename in files:
        handle(os.path.join(subdir, filename))
