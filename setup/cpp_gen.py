import collections
import os
import re
import subprocess
import sys

INCLUDES = [
    "algorithm",
    "bitset",
    "cassert",
    "cctype",
    "cmath",
    "complex",
    "cstddef",
    "cstdint",
    "cstdio",
    "cstring",
    "functional",
    "iostream",
    "map",
    "queue",
    "set",
    "string",
    "tuple",
    "unordered_map",
    "unordered_set",
    "utility",
    "vector",
]

DEBUG_LINES = [
    "#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED",
    "#include <boost/stacktrace.hpp>",
]
USING_NAMESPACE_STD = "using namespace std;"


def generate_includes():
    return ["#include <{}>".format(include) for include in INCLUDES] + [
        USING_NAMESPACE_STD
    ]


def generate_clean_lines(lines):
    DUMMY_LINE_PATTERN = re.compile(r"^\s*;*$")
    COMMENT_PATTERN = re.compile(r"^\s*//.*$")
    ANCHOR_LINES = ["// BEGIN KAWIGIEDIT TESTING", "// END KAWIGIEDIT TESTING"]

    res = []
    for line in lines:
        if line.startswith(b"#"):
            continue
        utf8_line = line.decode("utf-8")
        if utf8_line == USING_NAMESPACE_STD:
            continue
        if utf8_line not in ANCHOR_LINES and (
            DUMMY_LINE_PATTERN.match(utf8_line) or COMMENT_PATTERN.match(utf8_line)
        ):
            continue
        res.append(utf8_line)
    return res


def merge_adjacent_same_namespaces(lines):
    NAMESPACE_START = re.compile(r"^namespace (\S+) {")
    NAMESPACE_END = re.compile(r"^} // namespace (\S+)")

    named_lines = []
    current_namespace = None
    for line in lines:
        match = NAMESPACE_START.match(line)
        if match:
            current_namespace = match.group(1)
            continue
        match = NAMESPACE_END.match(line)
        if match:
            current_namespace = None
            continue
        if len(named_lines) > 0 and named_lines[-1][0] == current_namespace:
            named_lines[-1][1].append(line)
        else:
            named_lines.append((current_namespace, [line]))

    res = []
    for namespace, lines in named_lines:
        if namespace:
            res.append("namespace %s {" % namespace)
            res.extend(lines)
            res.append("} // %s" % namespace)
        else:
            res.extend(lines)
    return res


def gen_file(prefix, info, additional_contents=None, additional_args=None):
    proc = subprocess.Popen(
        [
            "g++",
            file_name,
            "-O2",
            "-std=c++14",
            "-I",
            os.path.join(os.environ["ICPC_HOME"], "Template"),
            "-E",
            "-nostdinc",
            "-nostdinc++",
            "-C",
        ]
        + (additional_args or []),
        stdout=subprocess.PIPE,
    )
    proc.wait()
    lines = generate_clean_lines(proc.stdout.read().split(b"\n"))
    lines = merge_adjacent_same_namespaces(lines)
    gen_file_name = prefix + file_name
    file = open(gen_file_name, "w")
    file.write(
        "\n".join(
            generate_includes()
            + (additional_contents if additional_contents else [])
            + lines
        )
    )
    file.close()
    subprocess.Popen(["clang-format", "-i", gen_file_name]).wait()
    with open(gen_file_name, "r") as input_file:
        subprocess.Popen(["pbcopy"], stdin=input_file).wait()
    print(
        """\033[92m
{separator}
! {gen_file_name} {info} !
{separator}
\033[0m""".format(
            gen_file_name=gen_file_name,
            separator="!" * (len(gen_file_name) + len(info) + 5),
            info=info,
        )
    )


if len(sys.argv) < 2:
    print("Please provide C++ file as the first argument.")
    sys.exit(1)
file_name = sys.argv[1]
if not file_name.endswith(".cpp"):
    print("Only support cpp file.")
    sys.exit(1)
if not os.path.exists(file_name):
    print("{} not found.".format(file_name))
    sys.exit(1)
gen_file(
    prefix="gendebug-",
    info="is generated",
    additional_contents=DEBUG_LINES,
    additional_args=["-DLOCAL"],
)
gen_file(prefix="gencpp-", info="is generated and copied to clipboard")
