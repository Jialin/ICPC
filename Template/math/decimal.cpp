namespace math {

template <typename T> inline int countDigits(T x) {
  int res = 1;
  for (x /= 10; x > 0; x /= 10, ++res) {
  }
  return res;
}

} // namespace math

namespace math {

template <typename T> inline int calcDigit(T x, int idx) {
  return x / constants::POW10[idx] % 10;
}

} // namespace math
