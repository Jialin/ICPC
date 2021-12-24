#pragma once

using namespace std;

namespace ds {

// Maintains intervals and groups adjcent intervals with the same value
template<typename Value, typename Key = int>
struct BaseValuedIntervalContainer {
  struct _Interval {
    Key lower, upper;
    Value v;

    inline _Interval(Key lower, Key upper, Value v)
        : lower(move(lower)), upper(move(upper)), v(move(v)) {}

    inline bool operator<(const _Interval& o) const {
      return lower < o.lower;
    }

#ifdef LOCAL
    inline friend ostream& operator<<(ostream& o, const _Interval& interval) {
      return o << '[' << interval.lower << ',' << interval.upper << "):" << interval.v;
    }
#endif
  };

  using Interval = _Interval;

  virtual inline void _insert(typename set<Interval>::iterator interval) {}
  virtual inline void _remove(typename set<Interval>::iterator interval) {}

  inline void emplace(Key lower, Key upper, Value v) {
    Interval interval(move(lower), move(upper), move(v));
    auto it = _intervals.lower_bound(interval);
    auto jt = it;
    Key frontLower = 0, frontUpper = 0;
    Value frontV;
    Key backLower = 0, backUpper = 0;
    Value backV;
    if (it != _intervals.begin()) {
      --it;
      assert(it->lower <= interval.lower);
      if (it->upper < interval.lower || (it->upper == interval.lower && it->v != interval.v)) {
        it = jt;
      } else if (it->v == interval.v) {
        if (interval.upper <= it->upper) {
          return;
        }
        interval.lower = move(it->lower);
      } else {
        frontLower = move(it->lower);
        frontUpper = interval.lower;
        frontV = it->v;
        backLower = move(interval.upper);
        backUpper = move(it->upper);
        backV = move(it->v);
      }
    }
    for (; jt != _intervals.end(); ++jt) {
      if (interval.upper < jt->lower || (interval.upper == jt->lower && jt->v != interval.v)) {
        break;
      }
      if (jt->upper <= interval.upper) {
        continue;
      }
      if (jt->v == interval.v) {
        interval.upper = move(jt->upper);
      } else {
        backLower = interval.upper;
        backUpper = move(jt->upper);
        backV = move(jt->v);
      }
    }
    while (it != jt) {
      auto kt = it;
      ++it;
      _remove(kt);
      _intervals.erase(kt);
    }
    if (frontLower < frontUpper) {
      _insert(_intervals.emplace(move(frontLower), move(frontUpper), move(frontV)).first);
    }
    _insert(_intervals.insert(move(interval)).first);
    if (backLower < backUpper) {
      _insert(_intervals.emplace(move(backLower), move(backUpper), move(backV)).first);
    }
  }

  set<Interval> _intervals;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const BaseValuedIntervalContainer& c) {
    return o << tostring(c._intervals);
  }
#endif
};

} // namespace ds
