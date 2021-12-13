#pragma once

using namespace std;

#ifdef LOCAL
struct Interval {
  int start, end;

  inline Interval() {}

  inline Interval(int start, int end) {
    this->start = start;
    this->end = end;
  }

  inline friend ostream& operator<<(ostream& o, const Interval& interval) {
    o << '(' << interval.start << ',' << interval.end << ')';
    return o;
  }
};
#endif
