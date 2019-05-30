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
#define INDEX(v,x) (CAST<int>(lower_bound(ALL(v),x)-BEGIN(v)))
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

  inline Fraction(T num, T den = 1, bool fixCoprime = true) {
    init(num, den, fixCoprime);
  }

  inline void init(T num, T den = 1, bool fixCoprime = true) {
    num_ = num;
    den_ = den;
    slightFix_();
    if (fixCoprime) fixCoprime_();
  }

  inline void initZero() {
    init(0, 1, false);
  }

  inline void initOne() {
    init(1, 1, false);
  }

  inline void initMediant(const Fraction& l, const Fraction& r, bool fixCoprime = true) {
    num_ = l.num_ + r.num_;
    den_ = l.den_ + r.den_;
    if (fixCoprime) fixCoprime_();
  }

  inline void updateMin(const Fraction &o) {
    if (o < *this) *this = o;
  }

  inline void updateMax(const Fraction &o) {
    if (*this < o) *this = o;
  }

  inline void updateInverse() {
    swap(num_, den_);
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

  inline bool operator>=(const Fraction &o) const {
    return !(*this < o);
  }

  inline bool operator<=(const Fraction &o) const {
    return *this == o || *this < o;
  }

  inline bool operator==(const Fraction& o) const {
    return num_ == o.num_ && den_ == o.den_;
  }

  inline bool operator!=(const Fraction& o) const {
    return num_ != o.num_ || den_ != o.den_;
  }

  inline void operator=(const Fraction& o) {
    num_ = o.num_;
    den_ = o.den_;
  }

  inline void operator-=(T v) {
    num_ -= v * den_;
    slightFix_();
  }

  inline void operator+=(T v) {
    num_ += v * den_;
    slightFix_();
  }

  inline void operator*=(T scale) {
    T g = gcd(scale, den_);
    num_ *= scale / g;
    den_ /= g;
    slightFix_();
  }

  /** floor(v-EPS) */
  /*********************************************************************************************************************
   * TO BE VERIFIED
   ********************************************************************************************************************/
  inline T floor(bool minusEps = false) const {
    if (!num_) return 0 - minusEps;
    if (num_ > 0) return (num_ - minusEps) / den_;
    return (num_ + (!minusEps)) / den_ - 1;
  }

  /** ceil(v+EPS) */
  /*********************************************************************************************************************
   * TO BE VERIFIED
   ********************************************************************************************************************/
  inline T ceil(bool plusEps = false) const {
    if (!num_) return 1;
    if (num_ > 0) return (num_ - !plusEps) / den_ + 1;
    return (num_ - plusEps) / den_;
  }

  inline bool isZero() const { return !num_; }

  /********************
   * TO BE VERIFIED
   *******************/
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
  */

  /** If l.den * r.num - l.num * r.den == 1, we could set fixCoprime to be false. */
  /*inline static Fraction mediant(const Fraction& l, const Fraction& r, bool fixCoprime = true) {
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

namespace testing {

template<typename T>
string toDisplay(const math::Fraction<T>& f) {
  ostringstream ss;
  ss << f.num() << "/" << f.den();
  return ss.str();
}
} // namespace testing

namespace math {

template<typename T = LL>
class ContinuedFraction {
public:
  inline void init(const Fraction<T>& v) {
    v_ = v;
    vs_.clear();
    vs_.push_back(v_.floor());
    v_ -= vs_.back();
    while (!v_.isZero()) {
      v_.updateInverse();
      vs_.push_back(v_.floor());
      v_ -= vs_.back();
    }
  }

  inline void push_back(T v) { vs_.push_back(v); }
  inline void pop_back() { vs_.pop_back(); }
  inline T& back() { return vs_.back(); }
  inline T& operator[](int idx) { return vs_[idx]; }
  inline const T& operator[](int idx) const { return vs_[idx]; }
  inline int size() const { return SIZE(vs_); }
private:
  vector<T> vs_;
  Fraction<T> v_;
}; // class ContinuedFraction
} // namespace math

namespace testing {

template<typename T>
string toDisplay(const math::ContinuedFraction<T>& cf) {
  ostringstream ss;
  if (cf.size() == 1) {
    ss << "[" << cf[0] << "]";
  } else {
    ss << "[" << cf[0];
    FOR(i, 1, cf.size()) ss << "," << cf[i];
    ss << "]";
  }
  return ss.str();
}
} // namespace testing

namespace math {

template<typename T = LL>
class BestFractionSolver {
public:
  /** Fraction with the minimum denominator which is larger than lower and smaller than upper. */
  inline bool calcNotInclude(const Fraction<T>& lower, const Fraction<T>& upper, Fraction<T>& res) {
    if (lower >= upper) return false;
    lowerCF_.init(lower);
    upperCF_.init(upper);
    T lowerLast = lowerCF_.back();
    T upperLast = upperCF_.back();
    bool first = true;
    FOR(dx, 0, 2) {
      if (dx && lowerLast) {
        --lowerCF_.back();
        lowerCF_.push_back(1);
      }
      FOR(dy, 0, 2) {
        if (dy && upperLast) {
          --upperCF_.back();
          upperCF_.push_back(1);
        }
        int idx;
        for (idx = 0; idx < lowerCF_.size() && idx < upperCF_.size() && lowerCF_[idx] == upperCF_[idx]; ++idx) {}
        if (idx >= lowerCF_.size()) {
          v_.init(upperCF_[idx] + 1);
        } else if (idx >= upperCF_.size()) {
          v_.init(lowerCF_[idx] + 1);
        } else {
          v_.init(min(lowerCF_[idx], upperCF_[idx]) + 1);
        }
        for (--idx ; idx >= 0; --idx) {
          v_.updateInverse();
          v_ += lowerCF_[idx];
        }
        if (v_ <= lower || upper <= v_) continue;
        if (first || res.den() > v_.den()) {
          res = v_;
          first = false;
        }
      }
      if (upperLast) {
        upperCF_.pop_back();
        ++upperCF_.back();
      }
    }
    return true;
  }
private:
  ContinuedFraction<T> lowerCF_, upperCF_;
  Fraction<T> v_;
}; // class BestFractionSolver
} // namespace math

const int MAXN = 10;

int n, xs[MAXN], ys[MAXN];
long long resX, resY;
math::Fraction<> lower, upper, updateF;
math::BestFractionSolver<> solver;

inline bool calc() {
  bool hasUpper = false;
  lower.initZero();
  FOR(i, 1, n) {
    int x = xs[i - 1] - xs[i];
    int y = ys[i] - ys[i - 1];
    if (!y) {
      if (x >= 0) return false;
      continue;
    }
    updateF.init(x, y);
    if (y > 0) {
      lower.updateMax(updateF);
    } else if (hasUpper) {
      upper.updateMin(updateF);
    } else {
      upper = updateF;
      hasUpper = true;
    }
  }
  LL lowerLL = lower.ceil(true);
  if (!hasUpper) {
    resX = 1;
    resY = lowerLL;
    return true;
  }
  if (lower >= upper) {
    return false;
  }
  solver.calcNotInclude(lower, upper, updateF);
  resX = updateF.den();
  resY = updateF.num();
  return true;
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d", &n);
    FOR(i, 0, n) scanf("%d%d", xs + i, ys + i);
    printf("Case #%d: ", taskIdx);
    if (calc()) {
      printf("%lld %lld\n", resX, resY);
    } else {
      puts("IMPOSSIBLE");
    }
  }
  return 0;
}
