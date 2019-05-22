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
