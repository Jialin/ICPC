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
#include "math/kitamasa/kitamasa_and_xor.h"

int n, m;
math::KitamasaAndXor<uint32_t> ki;
vector<uint32_t> xs, coefs;

int main() {
  while (scanf("%d%d", &n, &m) != EOF) {
    xs.resize(n);
    coefs.resize(n);
    for (int i = 0; i < n; ++i) {
      scanf("%u", &xs[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
      scanf("%u", &coefs[i]);
    }
    printf("%u\n", ki.calc(coefs, xs, m - 1));
  }
}