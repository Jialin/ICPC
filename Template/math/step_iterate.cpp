namespace math {

inline void stepIterate(int n, function<void(int, int, int)> processor) {
  int lastX = n;
  for (int y = 1; y <= n / y; ++y) {
    int x = n / (y + 1);
    processor(x + 1, lastX, y);
    lastX = x;
  }
  for (int x = lastX; x > 0; --x) {
    processor(x, x, n / x);
  }
}
} // namespace math

/*********************************************
 * Example: SPOJ SUMPRO
 *   sum(n / x * x for x in xrange(1, n + 1))
 *********************************************/
int calc(int n) {
  LL res = 0;
  math::stepIterate(n, [&res](int xLower, int xUpper, int y) {
    if (xLower == xUpper) {
      res += xLower * y;
    } else {
      res += (((xLower + xUpper) * (xUpper - xLower + 1LL)) >> 1) * y;
    }
  });
  return CAST<int>(res % 1000000007);
}

