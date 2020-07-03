#include <algorithm>
#include <bitset>
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

#include "math/prime/prime_iterator.h"

using namespace std;

math::PrimeIterator pi(100001);

int main() {
  int n;
  scanf("%d", &n);
  ++n;
  putchar(n <= 3 ? '1' : '2');
  putchar('\n');
  int last = 2;
  pi.iterate(n + 1, [&last, &n](int p) {
    if (p > n) {
      return;
    }
    for (int i = last; i < p; ++i) {
      putchar('2');
      putchar(' ');
    }
    putchar('1');
    putchar(' ');
    last = p + 1;
  });
  for (int i = last; i <= n; ++i) {
    putchar('2');
    putchar(' ');
  }
  putchar('\n');
}
