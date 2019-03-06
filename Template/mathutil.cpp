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

// Checks whether the number is in the form of 2^x
inline bool isPow2(int n) {
  return n && !(n & (n - 1));
}

// Computes the smallest 2^x which is not less than n.
inline int nextPow2(int n) {
  if (n <= 1) return 1;
  return isPow2(n) ? n : 1 << (32 - __builtin_clz(static_cast<unsigned int>(n)));
}
} // namespace mu
