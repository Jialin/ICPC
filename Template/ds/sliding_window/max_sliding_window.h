#pragma once

#include "ds/sliding_window/base_sliding_window_macros.h"

#include "ds/sliding_window/base_sliding_window.h"

namespace ds {

template<typename V>
struct MaxSlidingWindow final : BaseSlidingWindow<V> {
  inline bool cmp(const V& append, const V& last) const override {
    return append >= last;
  }
};

} // namespace ds
