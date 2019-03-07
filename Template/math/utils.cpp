namespace math { namespace utils {

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

// Generates primes
inline void generatePrimes(int n, vector<bool>& isPrime, vector<int>& primes) {
  isPrime.resize(n + 1);
  fill(isPrime.begin(), isPrime.end(), true);
  primes.clear();
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i <= n; ++i) if (isPrime[i]) {
    primes.push_back(i);
    if (i > n / i) continue;
    for (int j = i * i; j <= n; j += i) isPrime[j] = false;
  }
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
}} // namespace math::utils
