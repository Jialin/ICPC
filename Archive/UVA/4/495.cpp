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
// #define BIGINT_ADD_INLINE
// #define BIGINT_ADD_INLINE_INT
// #define BIGINT_ASSIGN
// #define BIGINT_ASSIGN_CHAR_ARRAY
#define BIGINT_ASSIGN_INT
// #define BIGINT_ASSIGN_STRING
// #define BIGINT_CLEAN
// #define BIGINT_CMP
// #define BIGINT_CMP_INT
// #define BIGINT_CONSTRUCT_EMPTY
// #define BIGINT_CONSTRUCT_INT
// #define BIGINT_DIGIT_COUNT
// #define BIGINT_DIGIT_SUM
// #define BIGINT_DIV_INLINE
// #define BIGINT_DIV_INLINE_INT
// #define BIGINT_DIV_MOD_INLINE_INT
// #define BIGINT_GCD_INLINE
// #define BIGINT_GT_INT
// #define BIGINT_INIT_ADD
// #define BIGINT_INIT_CAPACITY
// #define BIGINT_INIT_CHAR_ARRAY
// #define BIGINT_INIT_INT
// #define BIGINT_INIT_MUL
// #define BIGINT_LT
// #define BIGINT_MOD_DIV_INLINE
// #define BIGINT_MOD_INLINE
// #define BIGINT_MOD_INT
// #define BIGINT_MUL_INLINE_INT
// #define BIGINT_PRINT
// #define BIGINT_PRINT_CHAR_ARRAY
#define BIGINT_PRINT_QUICK
// #define BIGINT_SUB_INLINE

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/bigint.h"

const int MAXN = 5000 + 1;

math::BigInt<> fibs[MAXN];

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
    fibs[n].printQuick();
    io::writeChar('\n');
  }
  return 0;
}
