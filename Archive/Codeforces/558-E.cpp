// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/interval/base_grouping_intervals_container.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000 + 1;
const int MAXSIGMA = 26;

int Q_LOWER, Q_UPPER, BLOCK_IDX;

int cnts[MAXN][MAXSIGMA];
bool reversed[MAXN];

inline void moveSingle(int& fromV, int& toV, int& remain) {
  if (fromV) {
    int delta = min(fromV, remain);
    fromV -= delta;
    toV += delta;
    remain -= delta;
  }
}

inline void moveBack(int fromIdx, int toIdx, int size) {
  if (reversed[fromIdx]) {
    for (int i = 0; i < MAXSIGMA && size; ++i) {
      moveSingle(cnts[fromIdx][i], cnts[toIdx][i], size);
    }
  } else {
    for (int i = MAXSIGMA - 1; i >= 0 && size; --i) {
      moveSingle(cnts[fromIdx][i], cnts[toIdx][i], size);
    }
  }
}

struct CharContainer : ds::BaseGroupingIntervalsContainer<int, int> {
  inline void _beforeErase(IntervalIter interval) override {
    if (Q_UPPER < interval->second.upper) {
      //      |    |
      //   ||   ||
      // |         |
      moveBack(interval->second.id, BLOCK_IDX + 1, interval->second.upper - Q_UPPER);
      reversed[BLOCK_IDX + 1] = reversed[interval->second.id];
      moveBack(interval->second.id, BLOCK_IDX, Q_UPPER - max(Q_LOWER, interval->first));
    } else if (interval->first < Q_LOWER) {
      // |    |
      //   ||   ||
      moveBack(interval->second.id, BLOCK_IDX, interval->second.upper - Q_LOWER);
    } else {
      //    |  |
      // ||      ||
      moveBack(interval->second.id, BLOCK_IDX, interval->second.upper - interval->first);
    }
  }

  inline void _afterInsert(IntervalIter interval) override {
    if (interval->first == Q_LOWER && interval->second.upper == Q_UPPER) {
      ++BLOCK_IDX;
    } else if (Q_UPPER < interval->second.upper) {
      interval->second.id = BLOCK_IDX++;
    }
  }

  inline void print() {
    for (const auto& [lower, interval] : _intervals) {
      if (reversed[interval.id]) {
        FORR(i, MAXSIGMA - 1, 0) {
          char c = 'a' + i;
          FORR(j, cnts[interval.id][i] - 1, 0) {
            io::writeChar(c);
          }
        }
      } else {
        FOR(i, 0, MAXSIGMA) {
          char c = 'a' + i;
          FORR(j, cnts[interval.id][i] - 1, 0) {
            io::writeChar(c);
          }
        }
      }
    }
    io::writeChar('\n');
  }
};

const int MAXL = 100000 + 1;

char s[MAXL];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  io::readCharArray(s);
  CharContainer ic;
  int lastP = 0;
  FOR(i, 1, n + 1) {
    if (i == n || s[i - 1] != s[i]) {
      Q_LOWER = lastP;
      Q_UPPER = i;
      cnts[BLOCK_IDX][s[i - 1] - 'a'] = Q_UPPER - Q_LOWER;
      ic.emplace(Q_LOWER, Q_UPPER, BLOCK_IDX);
      lastP = i;
    }
  }
  FOR(_, 0, q) {
    int order;
    io::readInt(Q_LOWER);
    io::readInt(Q_UPPER);
    io::readInt(order);
    --Q_LOWER;
    reversed[BLOCK_IDX] = !order;
    ic.emplace(Q_LOWER, Q_UPPER, BLOCK_IDX);
  }
  ic.print();
  return 0;
}
