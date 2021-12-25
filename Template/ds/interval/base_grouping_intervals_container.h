#pragma once

using namespace std;

namespace ds {

// Maintains intervals and groups adjcent intervals with the same value
template<typename GroupID, typename Key = int>
struct BaseGroupingIntervalsContainer {
  struct _Interval {
    Key lower, upper;
    GroupID id;

    inline _Interval(Key lower, Key upper, GroupID id)
        : lower(move(lower)), upper(move(upper)), id(move(id)) {}

    inline bool operator<(const _Interval& o) const {
      return lower < o.lower;
    }

#ifdef LOCAL
    inline friend ostream& operator<<(ostream& o, const _Interval& interval) {
      return o << '[' << interval.lower << ',' << interval.upper << "):" << interval.id;
    }
#endif
  };

  using Interval = _Interval;
  using IntervalIter = typename set<Interval>::iterator;

  virtual inline void _beforeErase(IntervalIter interval) {}
  virtual inline void _afterInsert(IntervalIter interval) {}

  inline IntervalIter emplace(Key lower, Key upper, GroupID id) {
    Interval interval(move(lower), move(upper), move(id));
    auto it = _intervals.lower_bound(interval);
    auto jt = it;
    Key frontLower = 0, frontUpper = 0;
    GroupID frontID;
    Key backLower = 0, backUpper = 0;
    GroupID backID;
    if (it != _intervals.begin()) {
      --it;
      if (it->upper < interval.lower || (it->upper == interval.lower && it->id != interval.id)) {
        it = jt;
      } else if (it->id == interval.id) {
        if (interval.upper <= it->upper) {
          return it;
        }
        interval.lower = move(it->lower);
      } else {
        frontLower = move(it->lower);
        frontUpper = interval.lower;
        frontID = it->id;
        backLower = move(interval.upper);
        backUpper = move(it->upper);
        backID = move(it->id);
      }
    }
    for (; jt != _intervals.end(); ++jt) {
      if (interval.upper < jt->lower || (interval.upper == jt->lower && jt->id != interval.id)) {
        break;
      }
      if (jt->upper <= interval.upper) {
        continue;
      }
      if (jt->id == interval.id) {
        interval.upper = move(jt->upper);
      } else {
        backLower = interval.upper;
        backUpper = move(jt->upper);
        backID = move(jt->id);
      }
    }
    while (it != jt) {
      _beforeErase(it);
      it = _intervals.erase(it);
    }
    if (frontLower < frontUpper) {
      _afterInsert(_intervals.emplace(move(frontLower), move(frontUpper), move(frontID)).first);
    }
    auto res = _intervals.insert(move(interval)).first;
    _afterInsert(res);
    if (backLower < backUpper) {
      _afterInsert(_intervals.emplace(move(backLower), move(backUpper), move(backID)).first);
    }
    return res;
  }

  set<Interval> _intervals;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const BaseGroupingIntervalsContainer& c) {
    return o << tostring(c._intervals);
  }
#endif
};

} // namespace ds
