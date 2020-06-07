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
#include "math/gcd.h"

using namespace std;

int a, b;

inline long long calc() {
  if (math::gcd(a, b) != 1) {
    return -1;
  }
  return static_cast<long long>(a) * b - a - b + 1;
}

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    io::readInt(a);
    io::readInt(b);
    io::writeInt(calc());
    io::writeChar('\n');
  }
  return 0;
}
