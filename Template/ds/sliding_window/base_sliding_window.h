// !macro_gen
// ALL BASE_SLIDING_WINDOW_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename V>
struct BaseSlidingWindow {
  virtual inline bool cmp(const V& append, const V& last) const = 0;

#ifdef BASE_SLIDING_WINDOW_RESERVE // ^
  inline void reserve(int addCount) {
    _vs.reserve(addCount);
  }
#endif

  inline bool empty() {
    return _startPnt >= SIZE(_vs);
  }

  inline void init(int windowSize) {
    DEBUG_GE(windowSize, 1);
    _delta = windowSize - 1;
    _startPnt = 0;
    _vs.clear();
  }

  inline void push_back(int idx, V v) {
    for (; !empty() && cmp(v, _vs.back().second); _vs.pop_back()) {}
    popFrontUntilIdx(idx - _delta);
    _vs.emplace_back(idx, move(v));
  }

  inline const pair<int, V>& calc() const {
    DEBUG_LT(_startPnt, SIZE(_vs));
    return _vs[_startPnt];
  }

  // Pops front for all index less than <idx>
  inline void popFrontUntilIdx(int idx) {
    for (; !empty() && _vs[_startPnt].first < idx; ++_startPnt) {}
  }

  int _delta, _startPnt;
  vector<pair<int, V>> _vs;
};

} // namespace ds
