#pragma once

using namespace std;

namespace ds {

// Maintains intervals and groups adjcent intervals with the same value
template<typename GroupID, typename Key = int>
struct BaseGroupingIntervalsContainer {
  struct _Interval {
    Key upper;
    GroupID id;

    inline _Interval(Key upper, GroupID id) : upper(move(upper)), id(move(id)) {}

#ifdef LOCAL
    inline friend ostream& operator<<(ostream& o, const _Interval& interval) {
      return o << interval.upper << "):" << interval.id;
    }
#endif
  };

  using IntervalIter = typename map<Key, _Interval>::iterator;

  virtual inline void _beforeErase(IntervalIter interval) {}
  virtual inline void _afterInsert(IntervalIter interval) {}

  inline IntervalIter emplace(Key lower, Key upper, GroupID id) {
    auto it = _intervals.lower_bound(lower);
    auto jt = it;
    Key frontLower = 0, frontUpper = 0;
    GroupID frontID;
    Key backLower = 0, backUpper = 0;
    GroupID backID;
    if (it != _intervals.begin()) {
      --it;
      if (it->second.upper < lower || (it->second.upper == lower && it->second.id != id)) {
        it = jt;
      } else if (it->second.id == id) {
        if (upper <= it->second.upper) {
          return it;
        }
        lower = it->first;
      } else {
        frontLower = it->first;
        frontUpper = lower;
        frontID = it->second.id;
        backLower = upper;
        backUpper = move(it->second.upper);
        backID = move(it->second.id);
      }
    }
    for (; jt != _intervals.end(); ++jt) {
      if (upper < jt->first || (upper == jt->first && jt->second.id != id)) {
        break;
      }
      if (jt->second.upper <= upper) {
        continue;
      }
      if (jt->second.id == id) {
        upper = move(jt->second.upper);
      } else {
        backLower = upper;
        backUpper = move(jt->second.upper);
        backID = move(jt->second.id);
      }
    }
    while (it != jt) {
      _beforeErase(it);
      it = _intervals.erase(it);
    }
    if (frontLower < frontUpper) {
      _afterInsert(_intervals.emplace_hint(
          jt, move(frontLower), _Interval(move(frontUpper), move(frontID))));
    }
    auto res = _intervals.emplace_hint(jt, move(lower), _Interval(move(upper), move(id)));
    _afterInsert(res);
    if (backLower < backUpper) {
      _afterInsert(
          _intervals.emplace_hint(jt, move(backLower), _Interval(move(backUpper), move(backID))));
    }
    return res;
  }

  map<Key, _Interval> _intervals;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const BaseGroupingIntervalsContainer& c) {
    return o << tostring(c._intervals);
  }
#endif
};

} // namespace ds
