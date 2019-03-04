namespace mathutil {

  template<typename T>
  T gcd(T a, T b) {
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
} // mathutil
