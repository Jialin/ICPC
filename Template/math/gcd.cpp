namespace math {

template<typename T>
inline T gcd(T a, T b) {
  a = abs(a);
  b = abs(b);
  while (a && b) {
    if (a >= b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return a + b;
}
} // namespace math
