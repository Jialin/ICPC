#pragma once

#include "ds/rmq/base_rmq.h"

namespace ds {

template<typename V>
struct MaxRMQ : BaseRMQ<V> {
  inline void combine(const V& leftValue, const V& rightValue, V& res) const override {
    res = max(leftValue, rightValue);
  }
};

} // namespace ds
