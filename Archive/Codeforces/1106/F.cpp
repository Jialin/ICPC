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

#include "debug/debug.h"
#include "math/matrix/kitamasa.h"
#include "math/mod/root.h"

const int MOD = 998244353;
const int MOD_ROOT = 3;

math::LogModCoPrime<> logMod;
math::Kitamasa<> ki;

int main() {
  int n;
  scanf("%d", &n);
  vector<int> coef(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &coef[n - 1 - i]);
  }
  ki.init(coef, MOD - 1, 32);
  int exp, v;
  scanf("%d%d", &exp, &v);
  if (!v) {
    puts("-1");
    return 0;
  }
  vector<int> vs(n);
  vs[n - 1] = 1;
  int res = ki.calc(vs, exp - 1);
  bool exist;
  logMod.init(100003, false, 100000);
  int resBase = math::rootMod(res, v, MOD, MOD_ROOT, logMod, exist);
  printf("%d\n", exist ? resBase : -1);
}