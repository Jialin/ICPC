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

#define BIGINT_ASSIGN_INT
#define BIGINT_MUL_INT
#define BIGINT_OUTPUT_FAST
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/bigint/bigint.h"

const int MAXN = 1000 + 1;

math::BigInt<> facts[MAXN];

int main() {
  facts[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    facts[i] = facts[i - 1] * i;
  }
  int n;
  while (io::readInt(n)) {
    io::writeInt(n);
    io::writeChar('!');
    io::writeChar('\n');
    facts[n].outputFast();
    io::writeChar('\n');
  }
  return 0;
}
