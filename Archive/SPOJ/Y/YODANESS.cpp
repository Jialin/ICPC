// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 30000;
const int MAXL = 100000;

unordered_map<string, int> wordIdxs;
char word[MAXL];
ds::FenwickSum<int> fen;

int main() {
  fen.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    wordIdxs.clear();
    FOR(i, 0, n) {
      io::readCharArray(word);
      wordIdxs[word] = i;
    }
    fen.init(n);
    int res = 0;
    FOR(i, 0, n) {
      io::readCharArray(word);
      int j = wordIdxs[word];
      res += j - fen.calcPrefix(j);
      fen.update(j, 1);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
