// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_char_array.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000000 + 5;

int n;
char s[MAXN];

int main() {
  n = io::readCharArray(s);
  int minH = 0, maxH = 0, h = 0;
  FOR(i, 0, n) {
    if (s[i] == '(') {
      ++h;
      maxH = max(maxH, h);
    } else {
      --h;
      minH = min(minH, h);
    }
  }
  vector<int> prev(maxH - minH + 1, -1);
  int res = 0, resCnt = 1;
  h = -minH;
  prev[h] = 0;
  FOR(i, 0, n) {
    if (s[i] == '(') {
      prev[++h] = i + 1;
      continue;
    }
    prev[h--] = -1;
    if (prev[h] >= 0) {
      int curRes = i + 1 - prev[h];
      if (res < curRes) {
        res = curRes;
        resCnt = 1;
      } else if (res == curRes) {
        ++resCnt;
      }
    } else {
      prev[h] = i + 1;
    }
  }
  io::writeInt(res);
  io::writeChar(' ');
  io::writeInt(resCnt);
  io::writeChar('\n');
}
