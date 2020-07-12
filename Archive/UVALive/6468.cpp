#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/fib/pisano_period.h"

const int MAXN = 1000000;

math::MinPrimeTagger mpt;
math::PisanoPeriod pp(MAXN + 1, mpt);

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int idx, n;
    io::readInt(idx);
    io::readInt(n);
    io::writeInt(taskIdx + 1);
    io::writeChar(' ');
    io::writeInt(pp.calc(n));
    io::writeChar('\n');
  }
  return 0;
}
