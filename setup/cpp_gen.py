import os
import subprocess
import sys

INCLUDES = [
    "algorithm",
    "cassert",
    "cctype",
    "cmath",
    "cstddef",
    "cstdint",
    "cstdio",
    "cstring",
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


def default_includes():
    return ["#include <{}>".format(include) for include in INCLUDES]


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
    ],
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
        clean_lines.append(utf8_line)
gen_file_name = "gencpp_" + file_name
file = open(gen_file_name, "w")
file.write("\n".join(default_includes() + clean_lines))
file.close()
subprocess.Popen(["clang-format", "-i", gen_file_name])
print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
print("! " + gen_file_name + " is generated.")
print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
