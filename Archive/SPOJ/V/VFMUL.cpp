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
#define BIGINT_OUTPUT_FAST
#define FFT_UTILS_MUL_BIGINT

#include "math/bigint_macros.h"
#include "math/fft/fft_utils_macros.h"

#include "debug/debug.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "math/bigint/bigint.h"
#include "math/fft/fft_utils.h"

const int GROUP = 2;
const int MAXL = 300000 + GROUP * 5;

char s1[MAXL], s2[MAXL];
math::FFTUtils<double> fft((MAXL / GROUP) << 1);
math::BigInt<GROUP, int> a, b, c;

int main() {
  a.initCapacity(MAXL << 1);
  b.initCapacity(MAXL << 1);
  c.initCapacity(MAXL << 1);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readCharArray(s1);
    io::readCharArray(s2);
    a.initCharArray(s1);
    b.initCharArray(s2);
    fft.mul(a, b, c);
    c.outputFast();
    io::writeChar('\n');
  }
  return 0;
}
