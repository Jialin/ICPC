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

#define BIGINT_ADD
#define BIGINT_ASSIGN_INT
#define BIGINT_OUTPUT_FAST
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/bigint/bigint.h"

const int MAXN = 5000 + 1;

math::BigInt<9, int> fibs[MAXN];

int main() {
  fibs[0] = 0;
  fibs[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    fibs[i] = fibs[i - 2] + fibs[i - 1];
  }
  int n;
  while (io::readInt(n)) {
    io::writeCharArray("The Fibonacci number for ");
    io::writeInt(n);
    io::writeCharArray(" is ");
    fibs[n].outputFast();
    io::writeChar('\n');
  }
  return 0;
}
