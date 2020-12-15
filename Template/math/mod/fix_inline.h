#pragma once

#include <cassert>

#include "debug/debug.h"
#include "math/mod/slight_fix_inline.h"

namespace math {

template<typename V = int>
inline void fixModInline(V& v, const V& mod) {
  slightFixModInline<V>(v, mod);
  if (v < 0 || mod <= v) {
    DEBUG_GT(mod, 0);
    v %= mod;
    slightFixModInline<V>(v, mod);
  }
}

} // namespace math
