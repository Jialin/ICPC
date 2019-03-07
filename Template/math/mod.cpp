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

  inline Mod(T _v = 0) : v(fix(_v)) {}

  inline void operator =(T _v) {
    v = fix(_v);
  }

  inline void operator *=(T _v) {
    safeMul(v, fix(_v));
  }
}; // class Mod
}} // namespace math::mod
