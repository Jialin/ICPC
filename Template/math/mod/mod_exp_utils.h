#pragma once

#include <vector>

#include "math/mod/fix_inline.h"
#include "math/mod/mul_inline_safe.h"

using namespace std;

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
class ModExpUtils {
public:
  inline ModExpUtils(const V& base, const V& mod, const int& capacity = -1) {
    init(base, mod, capacity);
  }

  inline void init(const V& base, const V& mod, const int& capacity = -1) {
    mod_ = mod;
    pows_.clear();
    if (capacity > 0) {
      pows_.reserve(capacity);
    }
    pows_.emplace_back(base);
    fixModInline(pows_.back(), mod_);
  }

  template<typename EXP = int32_t>
  inline V exp(EXP e) {
    assert(e >= 0);
    V res = 1;
    fixModInline(res, mod_);
    for (size_t i = 0; e > 0; e >>= 1, ++i) {
      if (!(e & 1)) {
        continue;
      }
      while (i >= pows_.size()) {
        pows_.emplace_back(pows_.back());
        mulModInlineSafe<V, V_SQR>(pows_.back(), pows_.back(), mod_);
      }
      mulModInlineSafe<V, V_SQR>(res, pows_[i], mod_);
    }
    return res;
  }

private:
  V mod_;
  vector<V> pows_;
};

} // namespace math
