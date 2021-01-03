#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define FFT_UTILS_MUL_INLINE_COMPLEX_MATRIX
#include "math/fft/fft_utils_macros.h"

#include "debug/debug.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "math/fft/fft_utils.h"

const int MAXN = 400 + 2;
const int MAXPOW2 = 1 << 10;
const double EPS = 1E-5;

using COMPLEX_T = double;

int n, m, r, c, nr, mc, pow2;
char board[MAXN][MAXN], pattern[MAXN][MAXN];
math::FFTUtils<COMPLEX_T> fft(MAXPOW2);
bool valid[MAXN][MAXN];
vector<vector<math::Complex<COMPLEX_T>>> boardCs, patternCs;

int main() {
  io::readInt(n);
  io::readInt(m);
  for (int i = 0; i < n; ++i) {
    io::readCharArray(board[i]);
  }
  io::readInt(r);
  io::readInt(c);
  for (int i = 0; i < r; ++i) {
    io::readCharArray(pattern[i]);
  }
  boardCs.reserve(MAXPOW2);
  boardCs.resize(n + r);
  for (int i = 0; i < n + r; ++i) {
    boardCs[i].reserve(MAXPOW2);
    boardCs[i].resize(m + c);
    for (int j = 0; j < m + c; ++j) {
      boardCs[i][j].initPolar(1, math::PI / 13 * (board[i % n][j % m] - 'a'));
    }
  }
  patternCs.reserve(MAXPOW2);
  patternCs.resize(r);
  int patternCnt = 0;
  for (int i = 0; i < r; ++i) {
    patternCs[r - 1 - i].reserve(MAXPOW2);
    patternCs[r - 1 - i].resize(c);
    for (int j = 0; j < c; ++j) {
      if (pattern[i][j] == '?') {
        patternCs[r - 1 - i][c - 1 - j].init(0, 0);
      } else {
        patternCs[r - 1 - i][c - 1 - j].initPolar(
            1, -math::PI / 13 * (pattern[i][j] - 'a'));
        ++patternCnt;
      }
    }
  }
  fft.mulInline(boardCs, patternCs, true);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      io::writeChar(
          fabs(boardCs[i + r - 1][j + c - 1].real - patternCnt) < EPS ? '1'
                                                                      : '0');
    }
    io::writeChar('\n');
  }
}
