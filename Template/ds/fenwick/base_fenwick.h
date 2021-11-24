// !macro_gen
// ALL BASE_FENWICK_ALL
#pragma once

using namespace std;

namespace ds {

template<typename V>
struct BaseFenwick {
  virtual inline void initV(V& v) = 0;

  virtual inline void updateV(V& v, const V& deltaV) = 0;

#ifdef BASE_FENWICK_RESERVE // ^
  inline void reserve(int n) {
    _vs.reserve(n);
  }
#endif

  inline void init(int n) {
    _n = n;
    _vs.resize(n);
    for (auto& v : _vs) {
      initV(v);
    }
  }

  inline void update(int x, const V& deltaV) {
    for (int i = x; i < _n; i |= i + 1) {
      updateV(_vs[i], deltaV);
    }
  }

#ifdef BASE_FENWICK_CALC_PREFIX_RETURN // ^
  inline V calcPrefix(int x) {
    V res;
    calcPrefix(x, res);
    return res;
  }
#endif

  inline void calcPrefix(int x, V& res) {
    initV(res);
    for (int i = min(x, _n) - 1; i >= 0; --i) {
      updateV(res, _vs[i]);
      i &= i + 1;
    }
  }

#ifdef BASE_FENWICK_CALC_RANGE // ^
  virtual inline V subV(const V& upperV, const V& lowerV) const = 0;

  inline V calcRange(int lower, int upper) {
    if (lower >= upper || lower >= _n) {
      V res;
      initV(res);
      return res;
    }
    // BASE_FENWICK_CALC_RANGE => BASE_FENWICK_CALC_PREFIX_RETURN
    return lower ? subV(calcPrefix(upper), calcPrefix(lower)) : calcPrefix(upper);
  }
#endif

  int _n;
  vector<V> _vs;
};

} // namespace ds
