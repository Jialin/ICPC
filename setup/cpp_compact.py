import os
import re
import sys

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
compact_lines = []
with open(file_name, "r") as input_file:
    for line in input_file:
        if not re.search("['\"]", line):
            line = re.sub(r"^\s*", "", line)
            line = re.sub(r"(?<=\w)\s+(?=\W)", "", line)
            line = re.sub(r"(?<=\W)\s+(?=\w)", "", line)
            line = re.sub(r"(?<=\W)\s+(?=\W)", "", line)
        compact_lines.append(line)
output_file = open(file_name, "w")
output_file.write("".join(compact_lines))
output_file.close()
print(
    """
!!!!!!!!!!!!!!!!!!!
! {} is compacted.
!!!!!!!!!!!!!!!!!!!
""".format(
        file_name
    )
)
