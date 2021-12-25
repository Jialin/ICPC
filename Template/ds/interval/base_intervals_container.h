// !macro_gen
// ALL BASE_INTERVALS_CONTAINER_ALL
#pragma once

#include "ds/interval/base_intervals_container_macros.h"

using namespace std;

namespace ds {

// Maintains disjoint intervals
template<typename Key = int>
struct BaseIntervalsContainer {
  using IntervalIter = typename map<Key, Key>::iterator;

  virtual inline void _beforeErase(IntervalIter interval) {}
  virtual inline void _afterInsert(IntervalIter interval) {}

#ifdef BASE_INTERVALS_CONTAINER_EMPLACE // ^
  inline IntervalIter emplace(Key lower, Key upper) {
    auto it = _intervals.lower_bound(lower);
    auto jt = it;
    if (it != _intervals.begin()) {
      --it;
      if (it->second < lower) {
        it = jt;
      } else {
        if (upper <= it->second) {
          return it;
        }
        lower = move(it->first);
      }
    }
    for (; jt != _intervals.end() && jt->first <= upper; ++jt) {
      if (upper < jt->second) {
        upper = move(jt->second);
      }
    }
    while (it != jt) {
      _beforeErase(it);
      it = _intervals.erase(it);
    }
    auto res = _intervals.emplace(move(lower), move(upper)).first;
    _afterInsert(res);
    return res;
  }
#endif

#ifdef BASE_INTERVALS_CONTAINER_ERASE // ^
  inline void erase(Key lower, Key upper) {
    auto it = _intervals.lower_bound(lower);
    auto jt = it;
    Key frontLower = 0, frontUpper = 0;
    Key backLower = 0, backUpper = 0;
    if (it != _intervals.begin()) {
      --it;
      if (it->second <= lower) {
        it = jt;
      } else {
        frontLower = move(it->first);
        frontUpper = lower;
        if (upper <= it->second) {
          backLower = upper;
          backUpper = move(it->second);
        }
      }
    }
    for (; jt != _intervals.end() && jt->first < upper; ++jt) {
      if (upper < jt->second) {
        backLower = upper;
        backUpper = move(jt->second);
      }
    }
    while (it != jt) {
      _beforeErase(it);
      it = _intervals.erase(it);
    }
    if (frontLower < frontUpper) {
      _afterInsert(_intervals.emplace(move(frontLower), move(frontUpper)).first);
    }
    if (backLower < backUpper) {
      _afterInsert(_intervals.emplace(move(backLower), move(backUpper)).first);
    }
  }
#endif

  map<Key, Key> _intervals;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const BaseIntervalsContainer& c) {
    return o << tostring(c._intervals);
  }
#endif
};

} // namespace ds
