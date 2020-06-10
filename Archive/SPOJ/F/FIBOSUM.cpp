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
#include <utility>
#include <vector>

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/fib/fib_partial_sum.h"
#include "math/mod/sub.h"

using namespace std;

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n, m;
    io::readInt(n);
    io::readInt(m);
    io::writeInt(
        n <= m
            ? math::subMod(math::fibPartialSum(m), math::fibPartialSum(n - 1))
            : 0);
    io::writeChar('\n');
  }
  return 0;
}
