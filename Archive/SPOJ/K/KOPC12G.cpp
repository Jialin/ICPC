// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_2D_ARRAY_CALC_RANGE
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 500 + 1;

int n, q;
char board[MAXN][MAXN], word[MAXN];
ds::Fenwick2DArraySum<int, MAXN, MAXN> fen;

inline void update(int x, int y, char c) {
  int delta = c - 'A';
  fen.update(x, y, delta - (board[x][y] - 'A'));
  board[x][y] = c;
}

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readInt(n);
    io::readInt(q);
    fen.init(n, n);
    FOR(i, 0, n) {
      io::readCharArray(board[i]);
      FOR(j, 0, n) {
        fen.update(i, j, board[i][j] - 'A' + 1);
      }
    }
    FOR(_, 0, q) {
      int op;
      io::readInt(op);
      if (op) {
        int x1, y1, x2, y2;
        io::readInt(x1);
        io::readInt(y1);
        io::readInt(x2);
        io::readInt(y2);
        io::writeInt(fen.calcRange(x1, y1, x2 + 1, y2 + 1));
        io::writeChar('\n');
      } else {
        int x, y;
        io::readInt(x);
        io::readInt(y);
        io::readCharArray(word);
        if (x) {
          FOR(i, 0, n) {
            update(i, y, word[i]);
          }
        } else {
          FOR(j, 0, n) {
            update(y, j, word[j]);
          }
        }
      }
    }
  }
  return 0;
}
