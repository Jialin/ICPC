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

namespace {

inline int slightFix_(int a, int mod) {
  return a >= mod
      ? a - mod
      : a < 0 ? a + mod : a;
}

inline int fix_(int a, int mod) {
  a = slightFix_(a, mod);
  return 0 <= a && a < mod ? a : slightFix_(a % mod, mod);
}

inline int add_(int a, int b, int mod) {
  return fix_(a + b, mod);
}

inline int mul_(int a, int b, int mod) {
  a = fix_(a, mod);
  b = fix_(b, mod);
  return !a
      ? 0
      : b < mod / a ? a * b : static_cast<LL>(a) * b % mod;
}

inline int inv_(int a, int mod, int& x0, int& x1) {
  assert(extGcd(a, mod, x0, x1) == 1);
  return slightFix_(x0, mod);
}

} // namespace

class ModInt {
public:
  inline ModInt(int mod = 1000000007) : mod_(mod) {}

  inline int inv(int a) { return inv_(a, mod_, x0_, x1_); }
  inline int add(int a, int b) { return add_(a, b, mod_); }
  inline int mul(int a, int b) { return mul_(a, b, mod_); }
  inline int div(int a, int b) { return mul_(a, inv(b), mod_); }
private:
  int mod_;
  int x0_, x1_;
}; // class ModInt
} // namespace math

using math::ModInt;
