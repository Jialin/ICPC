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

#include "math/matrix/kitamasa_once.h"

int main() {
  int n;
  scanf("%d", &n);
  printf(
      "%d\n",
      n < 3 ? 0
            : math::KitamasaOnce<>().calc(
                  {1, 0, 1}, {1, 1, 1}, n - 3, 1000000007));
}