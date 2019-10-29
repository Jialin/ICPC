#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

namespace mu {

// Computes greatest common divisor
template<typename T>
inline T gcd(T a, T b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  while (a > 0 && b > 0) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return a + b;
}
} // namespace mu

int main() {
  int n, k;
  while (true) {
    scanf("%d%d", &n, &k);
    if (n < 0) break;
    long long a = ((k * (k - 1LL)) >> 1) - (k >> 1);
    long long b = n * (n - 1LL);
    long long gcd = mu::gcd(a, b);
    if (!a) {
      puts("0");
    } else {
      printf("%lld/%lld\n", a / gcd, b / gcd);
    }
  }
  return 0;
}
