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

namespace math { namespace utils {

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
}} // namespace math::utils

namespace math { namespace mod {

template<typename T, T MOD = 1000000007>
class Mod {
  static T fix(T v) {
    if (v < 0) {
      v += MOD;
      if (v < 0) v %= MOD;
      if (v < 0) v += MOD;
    } else if (v >= MOD) {
      v -= MOD;
      if (v >= MOD) v %= MOD;
    }
    return v;
  }

  static void safeAdd(T& x, T y) {
    x += y;
    return x >= MOD ? x - MOD : x;
  }

  static void safeMul(T& x, T y) {
    if (y == 0) {
      x = 0;
      return;
    }
    if (x < MOD / y) {
      x *= y;
      return;
    }
    x = static_cast<T>(static_cast<unsigned long long>(x) * y % MOD);
  }
public:
  T v;

  inline Mod(T v_ = 0) : v(fix(v_)) {}
  inline void operator =(T v_) { v = fix(v_); }
  inline void operator *=(T v_) { safeMul(v, fix(v_)); }
}; // class Mod
}} // namespace math::mod

const int MAXN = 50000;

vector<bool> isP;
vector<int> ps;
math::mod::Mod<int> res;

int main() {
  math::utils::generatePrimes(MAXN, isP, ps);
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n; scanf("%d", &n);
    res = 1;
    for (int p : ps) {
      if (p > n) break;
      int subRes = 1;
      for (int m = n / p; m > 0; m /= p) { subRes += m; }
      res *= subRes;
    }
    printf("%d\n", res.v);
  }
  return 0;
}
