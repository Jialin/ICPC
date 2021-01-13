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

#define BIGINT_INIT_CAPACITY
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_MUL_INLINE
#define BIGINT_OUTPUT_FAST
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "math/bigint/bigint.h"

const int GROUP = 6;
const int MAXL = 10000 + GROUP * 5;

math::BigInt<GROUP, int64_t, double> a, b;
char s1[MAXL], s2[MAXL];

int main() {
  a.initCapacity(MAXL << 1);
  b.initCapacity(MAXL << 1);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readCharArray(s1);
    io::readCharArray(s2);
    a.initCharArray(s1);
    b.initCharArray(s2);
    a *= b;
    a.outputFast();
    io::writeChar('\n');
  }
  return 0;
}
