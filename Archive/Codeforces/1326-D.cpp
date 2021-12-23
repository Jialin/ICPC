// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define MANACHER_CALC_CHAR_ARRAY
#define MANACHER_EVEN_LOWER
#define MANACHER_EVEN_UPPER
#define MANACHER_ODD_LOWER
#define MANACHER_ODD_UPPER
#define MANACHER_RESERVE
#include "string/palindrome/manacher_macros.h"

#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "string/palindrome/manacher.h"

// Last include
#include "debug/debug.h"

const int MAXL = 1000000 + 1;

inline void updateRes(pair<int, int>& res, int lower, int upper) {
  MMIN(lower, upper);
  if (res.second - res.first > upper - lower) {
    res.first = lower;
    res.second = upper;
  }
}

int L, R;

inline void updatePal(pair<int, int>& res, int lower, int upper) {
  if (!lower) {
    updateRes(res, L + upper - lower, R);
  }
  if (upper == R - L) {
    updateRes(res, L, R - upper + lower);
  }
}

str::Manacher man;

inline pair<int, int> calc(int n, pair<int, int>& res) {
  FOR(i, 0, n) {
    updatePal(res, man.oddLower(i), man.oddUpper(i));
    updatePal(res, man.evenLower(i), man.evenUpper(i));
  }
  return res;
}

char s[MAXL];

int main() {
  man.reserve(MAXL);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n = io::readCharArray(s);
    for (L = 0, R = n; L < R && s[L] == s[R - 1]; ++L, --R) {}
    pair<int, int> res{0, max(R - L, 0)};
    if (L < R) {
      man.calc(R - L, s + L);
      calc(R - L, res);
    }
    if (res.first >= res.second) {
      io::writeCharArray(s);
    } else {
      s[res.first] = '\0';
      io::writeCharArray(s);
      io::writeCharArray(s + res.second);
    }
    io::writeChar('\n');
  }
  return 0;
}
