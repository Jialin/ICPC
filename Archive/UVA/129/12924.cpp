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
#define BIGINT_CMP
#define BIGINT_INIT_ADD
#define BIGINT_MUL_INLINE
#define BIGINT_MUL_INLINE_INT
#define BIGINT_OUTPUT_FAST
#define BIGINT_SUB_INLINE
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/bigint/bigint.h"

using BigInt = math::BigInt<5, int64_t, double>;

inline pair<BigInt, BigInt> fib(int n) {
  BigInt a, b;
  if (!n) {
    a = 0;
    b = 1;
    return {move(a), move(b)};
  }
  tie(a, b) = fib(n >> 1);

  BigInt tmpC;
  tmpC.initAdd(b, b);
  tmpC -= a;
  BigInt c;
  c.initMul(a, tmpC);

  BigInt aa, bb;
  aa.initMul(a, a);
  bb.initMul(b, b);
  BigInt d;
  d.initAdd(aa, bb);

  if (n & 1) {
    c += d;
    return {move(d), move(c)};
  } else {
    return {move(c), move(d)};
  }
}

int main() {
  BigInt a, b;
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int na, nb, m;
    io::readInt(na);
    io::readInt(nb);
    io::readInt(m);
    if (!m) {
      io::writeInt(na);
      io::writeChar('\n');
      continue;
    }
    tie(a, b) = fib(m - 1);
    a *= na;
    b *= nb;
    a += b;
    a.outputFast();
    io::writeChar('\n');
  }
  return 0;
}
