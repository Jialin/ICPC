#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define CAST static_cast
#define SIZE(v) (CAST<int>((v).size()))
#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

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

namespace math {

template<typename T = LL>
class Fraction {
public:
  inline Fraction() {}

  inline Fraction(T num, T den, bool fixCoprime = true) {
    init(num, den, fixCoprime);
  }

  inline void init(T num, T den, bool fixCoprime = true) {
    num_ = num;
    den_ = den;
    slightFix_();
    if (fixCoprime) fixCoprime_();
  }

  inline bool operator<(const Fraction& o) const {
    if (*this == o) return false;
    if (num_ < 0 && o.num_ < 0) {
      return cmpNonNegative_(-o.num_, o.den_, -num_, den_);
    }
    if (num_ < 0) return true;
    if (o.num_ < 0) return false;
    return cmpNonNegative_(num_, den_, o.num_, o.den_);
  }

  inline bool operator==(const Fraction& o) const {
    return num_ == o.num_ && den_ == o.den_;
  }

  inline bool operator!=(const Fraction& o) const {
    return num_ != o.num_ || den_ != o.den_;
  }

  /**
   * TO BE VERIFIED
   */
  /*
  inline Fraction operator*(const T scale) const {
    T g = gcd(scale, den_);
    return Fraction(num_ * (scale / g), den_ / g, false);
  }

  inline Fraction operator+(const T v) const {
    return Fraction(num_ + den_ * v, den_, false);
  }

  inline Fraction operator+(const Fraction& o) const {
    T g = gcd(den_, o.den_);
    T newDen = den_ / g * o.den_;
    return Fraction(num_ * (newDen / den_) + o.num_ * (newDen / o.den_), newDen);
  }

  inline Fraction operator/(const T scale) const {
    T g = gcd(scale, num_);
    return Fraction(num_ / g, den_ * (scale / g), false);
  }

  inline void operator+=(const T v) {
    num_ += den_ * v;
  }

  inline void initMul(const Fraction& o, const T scale) {
    T g = gcd(scale, o.den_);
    num_ = o.num_ * (scale / g);
    den_ = o.den_ / g;
    slightFix_();
  }

  inline void initDiv(const Fraction &o, const T scale) {
    T g = gcd(scale, o.num_);
    num_ = o.num_ / g;
    den_ = o.den_ * (scale / g);
    slightFix_();
  }

  inline void initAdd(const Fraction &o, const T v) {
    num_ = o.num_ + v * o.den_;
    den_ = o.den_;
  }

  inline void initMediant(const Fraction& l, const Fraction& r, bool fixCoprime = true) {
    num_ = l.num_ + r.num_;
    den_ = l.den_ + r.den_;
    if (fixCoprime) fixCoprime_();
  }*/

  /** If l.den * r.num - l.num * r.den == 1, we could set fixCoprime to be false. */
  /*
  inline static Fraction mediant(const Fraction& l, const Fraction& r, bool fixCoprime = true) {
    return Fraction(l.num_ + r.num_, l.den_ + r.den_, fixCoprime);
  }*/

  inline T num() const { return num_; }
  inline T den() const { return den_; }

private:
  T num_, den_;

  inline void slightFix_() {
    if (num_ == 0) {
      den_ = 1;
    } else if (den_ < 0) {
      num_ = -num_;
      den_ = -den_;
    }
  }

  inline void fixCoprime_() {
    if (num_) {
      T g = gcd(num_, den_);
      num_ /= g;
      den_ /= g;
    }
  }

  inline static bool cmpNonNegative_(T num1, T den1, T num2, T den2) {
    if (!num2) return false;
    if (!num1) return true;
    bool overflow1 = LLONG_MAX / num1 < den2;
    bool overflow2 = LLONG_MAX / den1 < num2;
    if (!overflow1 && !overflow2) {
      return CAST<LL>(num1) * den2 < CAST<LL>(num2) * den1;
    }
    if (overflow1 && overflow2) {
      T v1 = num1 / den1;
      T v2 = num2 / den2;
      if (v1 != v2) {
        return v1 < v2;
      }
      num1 %= den1;
      num2 %= den2;
      if (!num2) return false;
      if (!num1) return true;
      return cmpNonNegative_(den2, num2, den1, num1);
    }
    return overflow2;
  }
}; // class Fraction

} // namespace math

const int MAXN = 300;
const int MAXM = MAXN * MAXN;

int n, m;
int xs[MAXN], ys[MAXN];
math::Fraction<> dis[MAXM];

inline int calc() {
  if (!m) return 1;
  sort(dis, dis + m);
  int res = 2;
  FOR(i, 1, m) res += dis[i - 1] != dis[i];
  return res;
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d", &n);
    FOR(i, 0, n) scanf("%d%d", xs + i, ys + i);
    m = 0;
    FOR(i, 0, n) FOR(j, i + 1, n) {
      LL x = xs[i] - xs[j];
      LL y = ys[j] - ys[i];
      if (!x || !y) continue;
      if (x < 0) {
        x = -x;
        y = -y;
      }
      if (y < 0) continue;
      dis[m++].init(y, x);
    }
    printf("Case #%d: %d\n", taskIdx, calc());
  }
  return 0;
}
