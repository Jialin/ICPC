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

#define BIGINT_ADD_INLINE
#define BIGINT_ASSIGN_INT
#define BIGINT_DIV_INLINE_INT
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_OUTPUT_FAST
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/bigint/bigint.h"

int n, m;
char s[32];
math::BigInt<> sum, v;

int main() {
  for (int taskIdx = 1;; ++taskIdx) {
    io::readInt(n);
    io::readInt(m);
    if (!n && !m) {
      break;
    }
    sum = 0;
    for (int i = 0; i < n; ++i) {
      io::readCharArray(s);
      v.initCharArray(s);
      sum += v;
    }
    io::writeCharArray("Bill #");
    io::writeInt(taskIdx);
    io::writeCharArray(" costs ");
    sum.outputFast();
    io::writeCharArray(": each friend should pay ");
    sum /= m;
    sum.outputFast();
    io::writeChar('\n');
    io::writeChar('\n');
  }
  return 0;
}
