// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define MANACHER_CALC_CHAR_ARRAY
#define MANACHER_LONGEST_PALINDROME
#include "string/palindrome/manacher_macros.h"

#include "io/read_char_array.h"
#include "io/write_char_array.h"
#include "string/palindrome/manacher.h"

// Last include
#include "debug/debug.h"

const int MAXL = 1000000 + 1;

char s[MAXL];

int main() {
  int n = io::readCharArray(s);
  str::Manacher man;
  man.calc(n, s);
  const auto& res = man.longestPalindrome();
  s[res.second] = '\0';
  io::writeCharArray(s + res.first);
  io::writeChar('\n');
  return 0;
}
