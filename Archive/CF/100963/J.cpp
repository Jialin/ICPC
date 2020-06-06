#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <tuple>
#include <vector>

#include "io/read_int.h"
#include "math/ext_gcd.h"

using namespace std;

inline long long
subCalc(const long long& a, const long long& b, const long long diff) {
  long long x, y;
  long long gcd = math::extGcd(a, b, x, y);
  if (diff % gcd) {
    return -1;
  }
  long long dx = b / gcd, dy = a / gcd;
  if (x < 0) {
    x += dx;
    y -= dy;
  }
  if (y > 0) {
    x += dx;
    y -= dy;
  }
  long long mul = diff / gcd;
  x *= mul;
  y *= mul;
  long long shift = min(x / dx, (-y) / dy);
  x -= dx * shift;
  y += dy * shift;
  return x;
}

inline long long calc(const long long& n,
                      const long long& m,
                      const long long& a,
                      const long long& k) {
  if (!m && !a) {
    return n == k ? n : -1;
  }
  if (!m) {
    return k <= n && !((n - k) % a) ? n : -1;
  }
  if (!a) {
    return n <= k && !((k - n) % m) ? k : -1;
  }
  if (k == n) {
    return n;
  }
  if (k > n) {
    long long res = subCalc(m, a, k - n);
    if (res < 0) {
      return -1;
    }
    return n + m * res;
  } else {
    long long res = subCalc(a, m, n - k);
    if (res < 0) {
      return -1;
    }
    return k + a * res;
  }
}

int main() {
  long long n, m, a, k;
  while (true) {
    io::readInt(n);
    io::readInt(m);
    io::readInt(a);
    io::readInt(k);
    if (!n && !m && !a && !k) {
      break;
    }
    long long res = calc(n, m, a, k + a);
    if (res >= 0) {
      printf("%lld\n", res);
    } else {
      puts("Impossible");
    }
  }
  return 0;
}
