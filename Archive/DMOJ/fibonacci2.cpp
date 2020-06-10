#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "io/read_char.h"
#include "io/write_int.h"
#include "math/fib/fib.h"

using namespace std;

constexpr int MOD = 1000000007;
constexpr long long FIB_MOD = 2000000016;

int main() {
  char ch;
  while (true) {
    ch = io::readChar();
    if (!isspace(ch)) {
      break;
    }
  }
  long long n = ch - '0';
  while (true) {
    ch = io::readChar();
    if (!isdigit(ch)) {
      break;
    }
    n *= 10;
    n += ch - '0';
    math::fixModInline(n, FIB_MOD);
  }
  int a, b;
  tie(a, b) = math::fib(n, MOD);
  io::writeInt(a);
  io::writeChar('\n');
}
