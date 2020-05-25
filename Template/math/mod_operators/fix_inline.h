#pragma once

#include <cassert>

#include "math/mod_operators/slight_fix_inline.h"

namespace math {

template <typename V = int32_t> inline void fixModInline(V &v, const V &mod) {
  slightFixModInline(v, mod);
  if (v < 0 || mod <= v) {
    assert(mod);
    v %= mod;
    slightFixModInline(v, mod);
  }
}

} // namespace math
