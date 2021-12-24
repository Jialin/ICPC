// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/base_valued_interval_container.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXSIGMA = 10 + 1;

int cnts[MAXSIGMA][MAXSIGMA];

struct Intervals : ds::BaseValuedIntervalContainer<int, int> {
  inline void _insert(typename set<Interval>::iterator interval) override {
    if (interval != _intervals.begin()) {
      auto prev = interval;
      --prev;
      if (prev->upper == interval->lower) {
        ++cnts[prev->v][interval->v];
      }
    }
    cnts[interval->v][interval->v] += interval->upper - interval->lower - 1;
    auto next = interval;
    ++next;
    if (next != _intervals.end() && interval->upper == next->lower) {
      ++cnts[interval->v][next->v];
    }
  }

  inline void _remove(typename set<Interval>::iterator interval) override {
    if (interval != _intervals.begin()) {
      auto prev = interval;
      --prev;
      if (prev->upper == interval->lower) {
        --cnts[prev->v][interval->v];
      }
    }
    cnts[interval->v][interval->v] -= interval->upper - interval->lower - 1;
    auto next = interval;
    ++next;
    if (next != _intervals.end() && interval->upper == next->lower) {
      --cnts[interval->v][next->v];
    }
  }
};

const int MAXL = 200000 + 1;

char s[MAXL], opS[MAXSIGMA];
int orders[MAXSIGMA];
Intervals intervals;

int main() {
  int n, q, sigma;
  io::readInt(n);
  io::readInt(q);
  io::readInt(sigma);
  io::readCharArray(s);
  int lastPos = 0;
  FOR(i, 1, n) {
    if (s[i - 1] != s[i]) {
      intervals.emplace(lastPos, i, s[i - 1] - 'a');
      lastPos = i;
    }
  }
  intervals.emplace(lastPos, n, s[n - 1] - 'a');
  FOR(_, 0, q) {
    int op;
    io::readInt(op);
    if (op == 1) {
      int lower, upper;
      io::readInt(lower);
      io::readInt(upper);
      io::readCharArray(opS);
      intervals.emplace(lower - 1, upper, opS[0] - 'a');
    } else {
      io::readCharArray(opS);
      FOR(i, 0, sigma) {
        orders[opS[i] - 'a'] = i;
      }
      int res = 1;
      FOR(i, 0, sigma) FORIF(j, 0, sigma, orders[i] >= orders[j]) {
        res += cnts[i][j];
      }
      io::writeInt(res, '\n');
    }
  }
  return 0;
}
