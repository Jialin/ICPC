#pragma once

#include <cassert>

#include "math/mod/slight_fix_inline.h"

namespace math {

template<typename V = int32_t>
inline void fixModInline(V& v, const V& mod) {
  slightFixModInline<V>(v, mod);
  if (v < 0 || mod <= v) {
    assert(mod);
    v %= mod;
    slightFixModInline<V>(v, mod);
  }
}

} // namespace math
