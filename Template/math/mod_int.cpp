/******************
 * TO BE VERIFIED.
 ******************/
namespace math {

inline int extGcd(int a, int b, int& x0, int& x1) {
  if (!b) {
    x0 = 1;
    x1 = 0;
    return a;
  }
  int gcd = extGcd(b, a % b, x0, x1);
  swap(x0, x1);
  x1 -= a / b * x0;
  return gcd;
}
} // namespace math

namespace math {

inline int slightFix(int a, int mod) {
  return a >= mod
      ? a - mod
      : a < 0 ? a + mod : a;
}

inline int fix(int a, int mod) {
  a = slightFix(a, mod);
  return 0 <= a && a < mod ? a : slightFix(a % mod, mod);
}

inline int add(int a, int b, int mod) {
  return fix(a + b, mod);
}

inline int mul(int a, int b, int mod) {
  a = fix(a, mod);
  b = fix(b, mod);
  return !a
      ? 0
      : b < mod / a ? a * b : static_cast<LL>(a) * b % mod;
}

inline int inv(int a, int mod, int& x0, int& x1) {
  assert(extGcd(a, mod, x0, x1) == 1);
  return slightFix(x0, mod);
}

class ModInt {
public:
  inline ModInt(int mod = 1000000007) : mod_(mod) {}

  inline int inv(int a) { return math::inv(a, mod_, x0, x1); }
  inline int add(int a, int b) { return math::add(a, b, mod_); }
  inline int mul(int a, int b) { return math::mul(a, b, mod_); }
  inline int div(int a, int b) { return math::mul(a, inv(b), mod_); }
private:
  int mod_;
  int x0, x1;
}; // class ModUtils
} // namespace math
