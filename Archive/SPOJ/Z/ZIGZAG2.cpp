// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 2000;
const int SHIFT = 11;
const int MASK = (1 << SHIFT) - 1;

int n, m, disCnt;
vector<int> as, bs, dis;
unordered_map<int, int> occLookup;
unordered_map<int, vector<int>> bIdxs;

inline void init() {
  occLookup.clear();
  io::readInt(n);
  as.resize(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
    occLookup[as[i]] |= 1;
  }
  io::readInt(m);
  bs.resize(m);
  FOR(i, 0, m) {
    io::readInt(bs[i]);
    occLookup[bs[i]] |= 2;
  }
  as.erase(
      remove_if(
          as.begin(),
          as.end(),
          [&](int v) {
            return occLookup[v] != 3;
          }),
      as.end());
  bs.erase(
      remove_if(
          bs.begin(),
          bs.end(),
          [&](int v) {
            return occLookup[v] != 3;
          }),
      bs.end());
  dis.clear();
  for (int v : as) {
    dis.push_back(v);
  }
  for (int v : bs) {
    dis.push_back(v);
  }
  SORTUNIQUE(dis);
  disCnt = SIZE(dis);
  for (int& v : as) {
    v = INDEX(dis, v);
  }
  for (int& v : bs) {
    v = INDEX(dis, v);
  }
  n = SIZE(as);
  m = SIZE(bs);
  bIdxs.clear();
  FOR(i, 0, m) {
    bIdxs[bs[i]].push_back(i);
  }
}

int taskIdx;

inline void initFenwick(
    int tags[MAXN][MAXN],
    vector<pair<int, int>> updates[MAXN],
    vector<pair<int, int>> calcs[MAXN],
    bool flip) {
  int expected;
  // calc
  expected = (taskIdx << 2) | 1;
  FOR(idx, 0, m) {
    calcs[idx].clear();
    for (int i = idx - 1; i >= 0; --i) {
      int v = flip ? disCnt - 1 - bs[idx] : bs[idx];
      for (int j = v - 1; j >= 0; --j) {
        if ((tags[i][j] & expected) == expected) {
          calcs[idx].emplace_back(i, j);
        }
        j &= j + 1;
      }
      i &= i + 1;
    }
    for (int i = idx; i < m; i |= i + 1) {
      int v = flip ? disCnt - 1 - bs[idx] : bs[idx];
      for (int j = v; j < disCnt; j |= j + 1) {
        if ((tags[i][j] >> 2) != taskIdx) {
          tags[i][j] = taskIdx << 2;
        }
        tags[i][j] |= 1;
      }
    }
  }
  // update
  expected = (taskIdx << 2) | 2;
  for (int idx = m - 1; idx >= 0; --idx) {
    updates[idx].clear();
    for (int i = idx; i < m; i |= i + 1) {
      int v = flip ? disCnt - 1 - bs[idx] : bs[idx];
      for (int j = v; j < disCnt; j |= j + 1) {
        if ((tags[i][j] & expected) == expected) {
          updates[idx].emplace_back(i, j);
        }
      }
    }
    for (int i = idx - 1; i >= 0; --i) {
      int v = flip ? disCnt - 1 - bs[idx] : bs[idx];
      for (int j = v - 1; j >= 0; --j) {
        if ((tags[i][j] >> 2) != taskIdx) {
          tags[i][j] = taskIdx << 2;
        }
        tags[i][j] |= 2;
        j &= j + 1;
      }
      i &= i + 1;
    }
  }
}

// ===up===
//   x
//  / \
// .
int upTags[MAXN][MAXN], upValues[MAXN][MAXN];
vector<pair<int, int>> upUpdates[MAXN], upCalcs[MAXN];
// ==down==
// .
//  \ /
//   x
int downTags[MAXN][MAXN], downValues[MAXN][MAXN];
vector<pair<int, int>> downUpdates[MAXN], downCalcs[MAXN];

int bestUp[MAXN], bestDown[MAXN];

inline int calcZigZag() {
  int res = 0;
  FOR(i, 0, n) {
    const auto& bIdx = bIdxs[as[i]];
    for (int _ = SIZE(bIdx) - 1; _ >= 0; --_) {
      int j = bIdx[_];
      // calc up
      int resUp = 0;
      for (auto [x, y] : downCalcs[j]) {
        if ((downValues[x][y] >> SHIFT) == taskIdx) {
          resUp = max(resUp, downValues[x][y] & MASK);
        }
      }
      // calc down
      int resDown = 0;
      for (auto [x, y] : upCalcs[j]) {
        if ((upValues[x][y] >> SHIFT) == taskIdx) {
          resDown = max(resDown, upValues[x][y] & MASK);
        }
      }
      // update up
      ++resUp;
      if ((bestUp[j] >> SHIFT) != taskIdx || (bestUp[j] & MASK) < resUp) {
        bestUp[j] = (taskIdx << SHIFT) | resUp;
        for (auto [x, y] : upUpdates[j]) {
          if ((upValues[x][y] >> SHIFT) != taskIdx) {
            upValues[x][y] = 0;
          }
          upValues[x][y] = (taskIdx << SHIFT) | max(upValues[x][y] & MASK, resUp);
        }
      }
      // update down
      ++resDown;
      if ((bestDown[j] >> SHIFT) != taskIdx || (bestDown[j] & MASK) < resDown) {
        bestDown[j] = (taskIdx << SHIFT) | resDown;
        for (auto [x, y] : downUpdates[j]) {
          if ((downValues[x][y] >> SHIFT) != taskIdx) {
            downValues[x][y] = 0;
          }
          downValues[x][y] = (taskIdx << SHIFT) | max(downValues[x][y] & MASK, resDown);
        }
      }
      res = max(max(res, resUp), resDown);
    }
  }
  return res;
}

inline int calc() {
  int res = calcZigZag();
  if (res > 2) {
    return res;
  }
  FOR(i, 0, n) FOR(j, i + 1, n) {
    if (as[i] == as[j]) {
      if (SIZE(bIdxs[as[i]]) > 1) {
        return 2;
      }
    } else {
      if (bIdxs[as[i]].front() < bIdxs[as[j]].back()) {
        return 2;
      }
    }
  }
  return n || m ? 1 : 0;
}

int main() {
  as.reserve(MAXN);
  bs.reserve(MAXN);
  dis.reserve(MAXN);
  int taskNumber;
  scanf("%d", &taskNumber);
  for (taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    init();
    initFenwick(upTags, upUpdates, upCalcs, true);
    initFenwick(downTags, downUpdates, downCalcs, false);
    io::writeInt(calc());
    io::writeChar('\n');
  }
  return 0;
}
