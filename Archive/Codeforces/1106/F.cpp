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
#include "math/kitamasa/kitamasa_once.h"
#include "math/mod/root.h"

const int MOD = 998244353;
const int MOD_ROOT = 3;

math::KitamasaOnce<> ki;
math::LogModCoPrime<> logMod;

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    vector<int> coefs(n);
    for (int i = n - 1; i >= 0; --i) {
      scanf("%d", &coefs[i]);
    }
    int exp, v;
    scanf("%d%d", &exp, &v);
    if (!v) {
      puts("-1");
      return 0;
    }
    vector<int> xs(n);
    xs[n - 1] = 1;
    int res = ki.calc(coefs, xs, exp - 1, MOD - 1);
    bool exist;
    logMod.init(100003, false, 100000);
    int resBase = math::rootMod(res, v, MOD, MOD_ROOT, logMod, exist);
    printf("%d\n", exist ? resBase : -1);
  }
}