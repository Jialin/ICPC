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
#include "io/write_char_array.h"
#include "string/palindrome/manacher.h"

// Last include
#include "debug/debug.h"

const int MAXL = 100000 + 1;

char s[MAXL];

int main() {
  str::Manacher man;
  man.reserve(MAXL);
  while (true) {
    int n = io::readCharArray(s);
    if (!n) {
      break;
    }
    man.calc(n, s);
    int res = n;
    FOR(i, 0, n) {
      if (man.oddUpper(i) == n) {
        MMIN(res, man.oddLower(i));
      }
      if (man.evenUpper(i) == n) {
        MMIN(res, man.evenLower(i));
      }
    }
    io::writeCharArray(s);
    reverse(s, s + res);
    s[res] = '\n';
    s[res + 1] = '\0';
    io::writeCharArray(s);
  }
  return 0;
}
