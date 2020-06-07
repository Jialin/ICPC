#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/linear_diophantine.h"

using namespace std;

int a, b, c, xmin, xmax, ymin, ymax;

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    io::readInt(a);
    io::readInt(b);
    io::readInt(c);
    io::readInt(xmin);
    io::readInt(xmax);
    io::readInt(ymin);
    io::readInt(ymax);
    io::writeCharArray("Case ");
    io::writeInt(taskIdx);
    io::writeCharArray(": ");
    io::writeInt(
        math::linearDiophantineSolutionCount(a, b, -c, xmin, xmax, ymin, ymax));
    io::writeChar('\n');
  }
  return 0;
}
