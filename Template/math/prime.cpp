namespace math {

/*******************************************************************************
 * TO BE VERIFY
 ******************************************************************************/
inline void generatePrimes(int n, vector<bool> &isPrime,
                           vector<int> *primes = nullptr) {
  isPrime.resize(n + 1);
  fill(isPrime.begin(), isPrime.end(), true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 4; i <= n; i += 2) {
    isPrime[i] = false;
  }
  for (int i = 3; i <= n && i <= n / i; ++i) {
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i << 1) {
        isPrime[j] = false;
      }
    }
  }
  if (primes) {
    primes->clear();
    for (int i = 2; i <= n; ++i) {
      if (isPrime[i]) {
        primes->push_back(i);
      }
    }
  }
}

} // namespace math
