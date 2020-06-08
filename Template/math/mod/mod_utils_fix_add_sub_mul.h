// @autogen
#pragma once

#include "math/mod/add.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"
#include "math/mod/sub.h"

namespace math {

template<
    typename V = int32_t,
    typename V_SQR = int64_t,
    typename V_DOUBLE = int32_t>
class ModUtils {
public:
  inline ModUtils(const V& mod) {
    init(mod);
  }

  inline void init(const V& mod) {
    mod_ = mod;
  }

  inline V fix(const V& a) const {
    return fixMod<V>(a, mod_);
  }

  inline V add(const V& a, const V& b) const {
    return addMod<V, V_DOUBLE>(a, b, mod_);
  }

  inline V sub(const V& a, const V& b) const {
    return subMod<V, V_DOUBLE>(a, b, mod_);
  }

  inline V mul(const V& a, const V& b) const {
    return mulMod<V, V_SQR>(a, b, mod_);
  }

private:
  V mod_;
};

} // namespace math
