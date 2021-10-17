// !macro_gen
// ALL BASE_SLIDING_WINDOW_ALL
#pragma once

#include <utility>

#include "common/macros.h"

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

  inline void init(int windowSize) {
    _delta = windowSize - 1;
    _startPnt = 0;
    _vs.clear();
  }

  inline void push_back(int idx, V v) {
    for (; _startPnt < SIZE(_vs) && cmp(v, _vs.back().second); _vs.pop_back()) {}
    for (; _startPnt < SIZE(_vs) && idx - _vs[_startPnt].first > _delta; ++_startPnt) {}
    _vs.emplace_back(idx, std::move(v));
  }

  inline const pair<int, V>& get() const {
    return _vs[_startPnt];
  }

  int _delta, _startPnt;
  vector<pair<int, V>> _vs;
};

} // namespace ds
