#pragma once

#include "ds/rmq/base_rmq.h"

namespace ds {

template<typename V>
struct MinRMQ : BaseRMQ<V> {
  inline void combine(const V& leftValue, const V& rightValue, V& res) const override {
    res = min(leftValue, rightValue);
  }
};

} // namespace ds
