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
#include "math/matrix/kitamasa_once.h"

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  printf(
      "%d\n",
      math::KitamasaOnce<>().calc(
          vector<int>(n, 1), vector<int>(n, 1), m - 1, 1000000007));
}