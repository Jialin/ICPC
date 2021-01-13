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

#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_LT_INT
#define BIGINT_MOD_INT
#define BIGINT_SUB_INLINE_INT
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "math/bigint/bigint.h"
#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"
#include "math/mod/sub.h"
#include "math/prime/phi_use_primes.h"
#include "math/prime/prime_generator.h"

const int MAXL = 1000000 + 2;
const int GROUP = 9;

math::PrimeGenerator pg(40000, 4203);
char s[MAXL];
math::BigInt<GROUP> bi;
int base;

int main() {
  while (scanf("%s", s) != EOF) {
    int mod;
    bi.initCharArray(s);
    scanf("%s%d", s, &mod);
    base = bi % mod;
    bi.initCharArray(s);
    bi -= 1;
    int res = math::subMod(base, 1, mod);
    if (bi < 32) {
      res = math::mulMod(res, math::expMod(base, bi[0], mod), mod);
    } else {
      int phi = math::phiUsePrimes(mod, pg.primes);
      res = math::mulMod(res, math::expMod(base, phi + bi % phi, mod), mod);
    }
    printf("%d\n", res ? res : mod);
  }
}
