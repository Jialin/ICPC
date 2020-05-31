#pragma once

#include <vector>

#include "math/mod_operators/fix_inline.h"
#include "math/mod_operators/mul_inline.h"

using namespace std;

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
class ModExpUtils {
public:
  inline ModExpUtils(const V& base = 2,
                     const V& mod = 1000000007,
                     const int& capacity = -1) {
    init(base, mod, capacity);
  }

  inline void
  init(const V& base, const V& mod = 1000000007, const int& capacity = -1) {
    mod_ = mod;
    pows_.clear();
    if (capacity > 0) {
      pows_.reserve(capacity);
    }
    pows_.emplace_back(base);
    fixModInline(pows_.back(), mod_);
  }

  template<typename EXP = int32_t>
  inline V exp(EXP exp) {
    assert(exp >= 0);
    V res = 1;
    fixModInline(res, mod_);
    for (size_t i = 0; exp > 0; exp >>= 1, ++i) {
      if (exp & 1) {
        while (i >= pows_.size()) {
          pows_.emplace_back(pows_.back());
          mulModInline<V, V_SQR>(pows_.back(), pows_.back(), mod_);
        }
        mulModInline<V, V_SQR>(res, pows_[i], mod_);
      }
    }
    return res;
  }

private:
  V mod_;
  vector<V> pows_;
};

} // namespace math
