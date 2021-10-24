#pragma once

#include "debug/debug_basic.h"
#include "ds/min_queue/base_min_queue.h"

namespace ds {

template<typename V>
struct MaxQueue : BaseMinQueue<V> {
  inline void addToStack(vector<pair<V, V>>& stack, pair<V, V>&& dirtyValue) const override {
    if (stack.empty()) {
      dirtyValue.second = dirtyValue.first;
    } else {
      dirtyValue.second = max(dirtyValue.first, stack.back().second);
    }
    stack.push_back(std::move(dirtyValue));
  }

  inline void calcEmpty(V& res) const override {
    DEBUG_TRUE(false);
  }

  inline void calcTailStackOnly(const pair<V, V>& tailValue, V& res) const override {
    res = tailValue.second;
  }

  inline void calcHeadStackOnly(const pair<V, V>& headValue, V& res) const override {
    res = headValue.second;
  }

  inline void
  combine(const pair<V, V>& headValue, const pair<V, V>& tailValue, V& res) const override {
    res = max(headValue.second, tailValue.second);
  }
};

} // namespace ds
