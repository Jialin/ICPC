#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "io/read_int.h"
#include "math/mod/fix.h"
#include "math/mod/mod_exp_utils.h"

using namespace std;

constexpr int MOD = 10000007;

math::ModExpUtils<> expN, expN1;

int main() {
  int n, k;
  while (true) {
    io::readInt(n);
    io::readInt(k);
    if (!n) {
      break;
    }
    expN.init(n, MOD, 32);
    expN1.init(n - 1, MOD, 32);
    int res = expN.exp(k) + (expN1.exp(k) << 1) + expN.exp(n) +
              (expN1.exp(n - 1) << 1);
    printf("%d\n", math::fixMod(res, MOD));
  }
  return 0;
}
