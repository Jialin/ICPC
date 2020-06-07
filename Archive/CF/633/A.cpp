#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <tuple>
#include <vector>

#include "io/read_int.h"
#include "io/write_char_array.h"
#include "math/ext_gcd.h"

using namespace std;

inline bool calc(int a, int b, int c) {
  int x, y;
  int gcd = math::extGcd(a, b, x, y);
  if (c % gcd) {
    return false;
  }
  int mul = c / gcd;
  x *= mul;
  y *= mul;
  int dx = b / gcd, dy = a / gcd;
  if (x < 0) {
    int shift = (-x + dx - 1) / dx;
    x += dx * shift;
    y -= dy * shift;
  } else {
    int shift = x / dx;
    x -= dx * shift;
    y += dy * shift;
  }
  return x >= 0 && y >= 0;
}

int main() {
  int a, b, c;
  io::readInt(a);
  io::readInt(b);
  io::readInt(c);
  io::writeCharArray(calc(a, b, c) ? "Yes" : "No");
  io::writeChar('\n');
  return 0;
}
