// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int n;
vector<int> prevs;
vector<int> nexts;

struct Range {
  int lower, upper, cnt;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const Range& range) {
    o << "[" << range.lower << "," << range.upper << "):" << range.cnt;
    return o;
  }
#endif

  inline Range(int lower, int upper, int cnt) : lower(lower), upper(upper), cnt(cnt) {}

  inline void moveUpperToCnt(int newCnt) {
    for (; cnt > newCnt; --upper) {
      if (prevs[upper - 1] < lower) {
        --cnt;
      }
    }
    for (; upper < n && cnt < newCnt; ++upper) {
      if (prevs[upper] < lower) {
        ++cnt;
      }
    }
    for (; upper < n; ++upper) {
      if (prevs[upper] < lower) {
        break;
      }
    }
  }

  inline void moveLower(int newLower) {
    for (; lower < newLower; ++lower) {
      if (upper <= nexts[lower]) {
        --cnt;
      }
    }
    for (; lower > newLower; --lower) {
      if (upper <= nexts[lower - 1]) {
        ++cnt;
      }
    }
  }
};

int main() {
  io::readInt(n);
  vector<int> vs(n);
  prevs.assign(n, -1);
  nexts.assign(n, n);
  vector<int> lastPs(n, -1);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
    --vs[i];
    int& lastP = lastPs[vs[i]];
    if (lastP >= 0) {
      nexts[lastP] = i;
      prevs[i] = lastP;
    }
    lastP = i;
  }
  vector<Range> ranges;
  ranges.reserve(n);
  FOR(i, 0, n) {
    ranges.emplace_back(i, i, 0);
    ranges.back().moveUpperToCnt(1);
    i = ranges.back().upper - 1;
  }
  vector<int> results(n);
  results[0] = ranges.size();
  vector<Range> newRanges;
  newRanges.reserve(n);
  FOR(cnt, 2, n + 1) {
    newRanges.clear();
    int pnt = 0;
    FOR(i, 0, n) {
      for (; ranges[pnt].upper <= i; ++pnt) {}
      if (abs(i - ranges[pnt].lower) < ranges[pnt].upper - i) {
        newRanges.push_back(ranges[pnt]);
        newRanges.back().moveLower(i);
      } else {
        newRanges.emplace_back(i, i, 0);
      }
      newRanges.back().moveUpperToCnt(cnt);
      i = newRanges.back().upper - 1;
    }
    swap(ranges, newRanges);
    results[cnt - 1] = ranges.size();
  }
  FOR(i, 0, n) {
    io::writeInt(results[i]);
    io::writeChar(i + 1 == n ? '\n' : ' ');
  }
  return 0;
}
