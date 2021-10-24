// !macro_gen
// ALL BASE_MIN_QUEUE_ALL
#pragma once

#include <utility>
#include <vector>

#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename UPDATE, typename V = UPDATE, typename RES = V>
struct BaseMinQueue {
  // Appends <value> to stack
  virtual inline void addToStack(vector<pair<UPDATE, V>>& stack, pair<UPDATE, V>&& value) const = 0;

  // Caculates result when the queue is empty
  virtual inline void calcEmpty(RES& res) const = 0;

  // Caculates result when head stack is empty
  virtual inline void calcTailStackOnly(const pair<UPDATE, V>& tailValue, RES& res) const = 0;

  // Caculates result when tail stack is empty
  virtual inline void calcHeadStackOnly(const pair<UPDATE, V>& headValue, RES& res) const = 0;

  // Combines values from the top of head stack and tail stack
  virtual inline void
  combine(const pair<UPDATE, V>& headValue, const pair<UPDATE, V>& tailValue, RES& res) const = 0;

#ifdef BASE_MIN_QUEUE_CLEAR // ^
  inline void clear() {
    _headStack.clear();
    _tailStack.clear();
  }
#endif

#ifdef BASE_MIN_QUEUE_RESERVE // ^
  inline void reserve(int capacity) {
    _headStack.reserve(capacity);
    _tailStack.reserve(capacity);
  }
#endif

  inline void push_back(pair<UPDATE, V>&& value) {
    addToStack(_tailStack, std::move(value));
  }

  inline void pop_front() {
    if (!_headStack.empty()) {
      _headStack.pop_back();
      return;
    }
    DEBUG_FALSE(_tailStack.empty());
    for (; _tailStack.size() > 1; _tailStack.pop_back()) {
      addToStack(_headStack, std::move(_tailStack.back()));
    }
    _tailStack.clear();
  }

  inline void calc(RES& res) {
    if (_headStack.empty()) {
      _tailStack.empty() ? calcEmpty(res) : calcTailStackOnly(_tailStack.back(), res);
    } else if (_tailStack.empty()) {
      calcHeadStackOnly(_headStack.back(), res);
    } else {
      combine(_headStack.back(), _tailStack.back(), res);
    }
  }

  vector<pair<UPDATE, V>> _headStack, _tailStack;
};

} // namespace ds
