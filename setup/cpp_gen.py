import os
import subprocess
import sys
import re

INCLUDES = [
    "algorithm",
    "bitset",
    "cassert",
    "cctype",
    "cmath",
    "cstddef",
    "cstdint",
    "cstdio",
    "cstring",
    "functional",
    "iostream",
    "map",
    "set",
    "string",
    "tuple",
    "unordered_map",
    "unordered_set",
    "utility",
    "vector",
]
DUMMY_LINE_PATTERN = re.compile(r"^\s*;$")
COMMENT_PATTERN = re.compile(r"^\s*//.*$")


def default_includes():
    return ["#include <{}>".format(include) for include in INCLUDES]


def gen_file(prefix, info, additional_args=None):
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
    clean_lines = []
    using_std = False
    for line in proc.stdout.read().split(b"\n"):
        if not line.startswith(b"#"):
            utf8_line = line.decode("utf-8")
            if utf8_line == "using namespace std;":
                if using_std:
                    continue
                using_std = True
            if DUMMY_LINE_PATTERN.match(utf8_line) or COMMENT_PATTERN.match(utf8_line):
                continue
            clean_lines.append(utf8_line)
    gen_file_name = prefix + file_name
    file = open(gen_file_name, "w")
    file.write("\n".join(default_includes() + clean_lines))
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
gen_file(prefix="gendebug-", info="is generated", additional_args=["-DLOCAL"])
gen_file(prefix="gencpp-", info="is generated and copied to clipboard")
