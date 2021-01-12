import os
import re
import subprocess
from copy import deepcopy

TEMPLATES = ["math/mod/mod_int.h", "math/complex/complex.h"]


def generate_dep_lines(dep_from, dep_tos):
    return (
        ["#ifdef " + dep_from]
        + ["#define " + dep_to for dep_to in sorted(dep_tos)]
        + ["#endif"]
    )


def write_macro_file(macro_filepath, lines):
    with open(macro_filepath, "r") as macro_file:
        original_lines = macro_file.readlines()
    file = open(macro_filepath, "w")
    file.write("\n".join(lines))
    file.close()
    subprocess.Popen(["clang-format", "-i", macro_filepath]).wait()
    with open(macro_filepath, "r") as macro_file:
        new_lines = macro_file.readlines()
    if original_lines != new_lines:
        print("{} updated.".format(macro_filepath))


ALL_DECLARE_PATTERN = re.compile(r"^.*// ALL ([A-Z_]+)$")
ALL_DEPS_PATTERN = re.compile(r"^.*// \^ ([A-Z_]+)$")
DEPS_PATTERN = re.compile(r"^.*//\s*([A-Z_]+) => ([A-Z_]+)\s*$")
for template in TEMPLATES:
    template_filepath = os.path.join(os.environ["ICPC_HOME"], "Template", template)
    deps = {}
    all_deps = set()
    # Load all_deps and deps
    with open(template_filepath, "r") as template_file:
        for line in template_file.readlines():
            match = ALL_DECLARE_PATTERN.match(line)
            if match:
                all_dep = match[1]
                continue
            match = ALL_DEPS_PATTERN.match(line)
            if match:
                all_deps.add(match[1])
                continue
            match = DEPS_PATTERN.match(line)
            if match:
                dep_from = match[1]
                dep_to = match[2]
                if dep_from not in deps:
                    deps[dep_from] = set()
                deps[dep_from].add(dep_to)
    # Propagage deps
    while True:
        new_deps = deepcopy(deps)
        for dep_from, dep_tos in deps.items():
            for dep_to in dep_tos:
                new_deps[dep_from] |= deps.get(dep_to, set())
        if deps == new_deps:
            break
        deps = new_deps
    # Generate codes
    lines = generate_dep_lines(all_dep, all_deps)
    for dep_from, dep_tos in sorted(deps.items()):
        lines.append("")
        lines.extend(generate_dep_lines(dep_from, dep_tos))
    # Write file
    macro_filepath = re.sub(".h$", "_macros.h", template_filepath)
    write_macro_file(macro_filepath, lines)
