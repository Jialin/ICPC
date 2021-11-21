// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

int as[MAXN], cnts[MAXN];

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, q;
    io::readInt(n);
    io::readInt(q);
    FOR(i, 0, n) {
      io::readInt(as[i]);
    }
    cnts[0] = 0;
    FOR(i, 1, n) {
      cnts[i] = cnts[i - 1] + (as[i - 1] != as[i]);
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeCharArray(":\n");
    FOR(_, 0, q) {
      int x, y;
      io::readInt(x);
      io::readInt(y);
      io::writeInt(cnts[y - 1] - cnts[x - 1] + 1);
      io::writeChar('\n');
    }
  }
  return 0;
}
