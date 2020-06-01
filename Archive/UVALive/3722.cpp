#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/mod_operators/mod_exp_utils.h"
#include "math/mod_operators/mod_utils_fix_add_sub_mul.h"

using namespace std;

int x, alpha, mod;
math::ModUtils<> mu;
math::ModExpUtils<> meu;

inline int calc(int n) {
  if (n == 1) {
    return mu.fix(1);
  }
  if (n & 1) {
    return mu.add(mu.mul(calc(n - 1), alpha), 1);
  } else {
    return mu.mul(calc(n >> 1), mu.add(meu.exp(n >> 1), 1));
  }
}

int main() {
  int n;
  while (true) {
    io::readInt(x);
    if (!x) {
      break;
    }
    io::readInt(alpha);
    io::readInt(n);
    io::readInt(mod);
    mu.init(mod);
    meu.init(alpha, mod);
    int alphaN = meu.exp(n);
    io::writeInt(mu.sub(mu.mul(x, alphaN), mu.mul(calc(n), alpha)));
    io::writeChar('\n');
  }
  return 0;
}
