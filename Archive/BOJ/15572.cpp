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
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#include "debug/debug.h"
#include "math/matrix/kitamasa_once.h"
#include "math/mod/sub.h"

const int MOD = 1999;

math::KitamasaOnce<int, int> ki;
vector<int> coef, vs, two;

// https://www.acmicpc.net/problem/15572
int main() {
  int n;
  int64_t m;
  scanf("%d%lld", &n, &m);
  two.resize(n + 1);
  two[0] = 1;
  for (int i = 1; i <= n; ++i) {
    two[i] = math::addMod(two[i - 1], two[i - 1], MOD);
  }
  vs.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    vs[i] = two[i];
  }
  vs[n - 1] = math::subMod(two[n], 1, MOD);
  coef.assign(n, 1);
  coef[0] = two[n - 1];
  printf("%d\n", ki.calc(coef, vs, m - 1, MOD));
}
