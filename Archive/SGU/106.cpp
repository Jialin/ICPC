#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <tuple>
#include <vector>

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/linear_diophantine.h"

using namespace std;

int main() {
  int a, b, c, xmin, xmax, ymin, ymax;
  io::readInt(a);
  io::readInt(b);
  io::readInt(c);
  io::readInt(xmin);
  io::readInt(xmax);
  io::readInt(ymin);
  io::readInt(ymax);
  io::writeInt(
      math::linearDiophantineSolutionCount(a, b, -c, xmin, xmax, ymin, ymax));
  io::writeChar('\n');
  return 0;
}
