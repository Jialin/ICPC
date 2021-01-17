import os
import re
import subprocess
from copy import deepcopy

TEMPLATES = [
    "math/bigint/bigint.h",
    "math/complex/complex.h",
    "math/fft/fft_utils.h",
    "math/fft/fft_mul_utils.h",
    "math/fft/ntt_utils.h",
    "math/fft/ntt_mul_utils.h",
    "math/mod/mod_int.h",
    "math/poly/fft_poly.h",
    "math/poly/ntt_poly_mod_int.h",
]


def generate_dep_lines(dep_from, dep_tos):
    return (
        (["#ifdef " + dep_from] if dep_from else [])
        + ["#define " + dep_to for dep_to in sorted(dep_tos)]
        + (["#endif"] if dep_from else [])
    )


def write_macro_file(macro_filepath, lines):
    try:
        with open(macro_filepath, "r") as macro_file:
            original_lines = macro_file.readlines()
    except:
        original_lines = []
    file = open(macro_filepath, "w")
    file.write("\n".join(lines))
    file.close()
    subprocess.Popen(["clang-format", "-i", macro_filepath]).wait()
    with open(macro_filepath, "r") as macro_file:
        new_lines = macro_file.readlines()
    if original_lines != new_lines:
        print("{} updated.".format(macro_filepath))


ALL_DECLARE_PATTERN = re.compile(r"^.*// ALL ([A-Z0-9_]+)$")
ALL_DEPS_PATTERN = re.compile(r"^.*// \^ ([A-Z0-9_]+)$")
DEPS_PATTERN = re.compile(r"^.*//\s*([A-Z0-9_]+) => ([A-Z0-9_]+)\s*$")
GLOBAL_DEPS_PATTERN = re.compile(r"^.*//\s* => ([A-Z0-9_]+)\s*$")
INCLUDE_PATTERN = re.compile(r"^(#include \S+)\s*// INCLUDE$")
for template in TEMPLATES:
    template_filepath = os.path.join(os.environ["ICPC_HOME"], "Template", template)
    all_dep = ""
    deps = {}
    all_deps = set()
    global_deps = set()
    includes = set()
    # Load all_deps and deps
    with open(template_filepath, "r") as template_file:
        for line in template_file.readlines():
            match = ALL_DECLARE_PATTERN.match(line)
            if match:
                all_dep = match[1]
                continue
            match = INCLUDE_PATTERN.match(line)
            if match:
                includes.add(match[1])
                continue
            match = ALL_DEPS_PATTERN.match(line)
            if match:
                all_deps.add(match[1])
                continue
            match = GLOBAL_DEPS_PATTERN.match(line)
            if match:
                global_deps.add(match[1])
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
    if lines:
        lines.append("")
    lines.extend(generate_dep_lines("", global_deps))
    for dep_from, dep_tos in sorted(deps.items()):
        if lines:
            lines.append("")
        lines.extend(generate_dep_lines(dep_from, dep_tos))
    if lines:
        lines.append("")
    lines.extend(sorted(includes))
    if lines and lines[-1]:
        lines.append("")
    # Write file
    macro_filepath = re.sub(".h$", "_macros.h", template_filepath)
    write_macro_file(macro_filepath, lines)
