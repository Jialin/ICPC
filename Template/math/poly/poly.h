// !macro_gen
// ALL POLY_ALL
#pragma once

#include "common/macros.h"

#include "math/poly/poly_macros.h"

namespace math {

template<typename V>
struct Poly : public vector<V> {
#ifdef POLY_CONSTRUCT // ^
  inline Poly(int size, V v) : vector<V>(size, v) {}
#endif

#ifdef POLY_ASSIGN // ^
  inline void operator=(const Poly& o) {
    this->resize(o.size());
    FORSIZE(i, o) {
      (*this)[i] = o[i];
    }
  }
#endif

#ifdef POLY_ASSIGN_VECTOR // ^
  template<typename OV>
  inline void operator=(const vector<OV>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const Poly& vs) {
    o << tostring(static_cast<vector<V>>(vs));
    return o;
  }
#endif
};

} // namespace math
