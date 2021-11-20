// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 2000 + 5;
const int SHIFT = 11;
const int MASK = (1 << SHIFT) - 1;

int n, m;
int tags[MAXN][MAXN];

struct Garland {
  int cnt;
  vector<int64_t> preSums;
  int lastX, lastY;

  inline void init(int idx) {
    io::readInt(cnt);
    preSums.resize(cnt);
    FOR(i, 0, cnt) {
      int x, y, w;
      io::readInt(x);
      io::readInt(y);
      io::readInt(w);
      lastX = x;
      lastY = y;
      tags[x][y] = (idx << SHIFT) | i;
      preSums[i] = i ? preSums[i - 1] + w : w;
    }
  }

  inline bool isLastCovered(int x1, int y1, int x2, int y2) {
    return x1 <= lastX && lastX <= x2 && y1 <= lastY && lastY <= y2;
  }

  inline int64_t calc(int inIdx, int outIdx) {
    if (inIdx + 1 == outIdx) {
      return preSums[inIdx];
    }
    if (outIdx + 1 == inIdx) {
      return -preSums[outIdx];
    }
    return 0;
  }
};

Garland garlands[MAXN];
char ops[8];
vector<bool> isOffs;

inline void calc(int inTag, int outTag, int64_t& res) {
  if (inTag >= 0 && outTag >= 0 && !isOffs[inTag >> SHIFT] &&
      (inTag >> SHIFT) == (outTag >> SHIFT)) {
    res += garlands[inTag >> SHIFT].calc(inTag & MASK, outTag & MASK);
  }
}

int main() {
  memset(tags, 0xFF, sizeof(tags));
  int k;
  io::readInt(n);
  io::readInt(m);
  io::readInt(k);
  FOR(i, 0, k) {
    garlands[i].init(i);
  }
  isOffs.assign(k, false);
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    io::readCharArray(ops);
    if (ops[0] == 'S') {
      int idx;
      io::readInt(idx);
      --idx;
      isOffs[idx] = !isOffs[idx];
    } else {
      int x1, y1, x2, y2;
      io::readInt(x1);
      io::readInt(y1);
      io::readInt(x2);
      io::readInt(y2);
      int64_t res = 0;
      FOR(i, 0, k) {
        if (!isOffs[i] && garlands[i].isLastCovered(x1, y1, x2, y2)) {
          res += garlands[i].preSums.back();
        }
      }
      FOR(i, x1, x2 + 1) {
        // left
        calc(tags[i][y1], tags[i][y1 - 1], res);
        // right
        calc(tags[i][y2], tags[i][y2 + 1], res);
      }
      FOR(j, y1, y2 + 1) {
        // up
        calc(tags[x1][j], tags[x1 - 1][j], res);
        // down
        calc(tags[x2][j], tags[x2 + 1][j], res);
      }
      io::writeInt(res);
      io::writeChar('\n');
    }
  }
}
