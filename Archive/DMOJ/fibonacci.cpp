#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "math/fib/fib.h"

using namespace std;

const int MOD = 1000000007;

int main() {
  unsigned long long n;
  scanf("%llu", &n);
  printf("%d\n", math::fib(n, MOD).first);
}
