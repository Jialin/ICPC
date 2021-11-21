// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_RANGE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;
const int MAXBIT = 27;

const int BITSHIFT = 17;
const int BITCNT = 7;

const int MAXFEN = (MAXBIT + BITCNT - 1) / BITCNT;
const __int128_t ONE = 1;

int as[MAXN];
ds::FenwickSum<__int128_t> fens[MAXFEN];
char subOp[4];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  FOR(i, 0, MAXFEN) {
    fens[i].init(n);
  }
  FOR(i, 0, n) {
    int x;
    io::readInt(x);
    as[i] = x;
    for (int bit = 0; bit < MAXBIT && x; bit += BITCNT, x >>= BITCNT) {
      __int128_t mask = 0;
      for (int j = 0, shift = 0; j < BITCNT; ++j, shift += BITSHIFT) {
        if (x & (1 << j)) {
          mask |= ONE << shift;
        }
      }
      if (mask) {
        fens[bit / BITCNT].update(i, mask);
      }
    }
  }
  FOR(_, 0, q) {
    int op;
    io::readInt(op);
    if (op == 1) {
      int x, idx;
      io::readInt(x);
      io::readInt(idx);
      --idx;
      int y = as[idx] ^ x;
      as[idx] = x;
      for (int bit = 0; bit < MAXBIT && (x || y); bit += BITCNT, x >>= BITCNT, y >>= BITCNT) {
        __int128_t mask = 0;
        for (int j = 0, shift = 0; j < BITCNT; ++j, shift += BITSHIFT) {
          if (!(y & (1 << j))) {
            continue;
          }
          if (x & (1 << j)) {
            mask += ONE << shift;
          } else {
            mask -= ONE << shift;
          }
        }
        if (mask) {
          fens[bit / BITCNT].update(idx, mask);
        }
      }
    } else {
      int lower, upper;
      io::readCharArray(subOp);
      io::readInt(lower);
      io::readInt(upper);
      --lower;
      int64_t res = 0;
      for (int bit = 0; bit < MAXBIT; bit += BITCNT) {
        auto mask = fens[bit / BITCNT].calcRange(lower, upper);
        for (int j = 0; j < BITCNT; ++j, mask >>= BITSHIFT) {
          int64_t oneCnt = mask & ((1 << BITSHIFT) - 1);
          int64_t zeroCnt = upper - lower - oneCnt;
          int64_t subRes = 0;
          if (subOp[0] == 'O' || subOp[0] == 'A') {
            subRes += ((oneCnt - 1) * oneCnt) >> 1;
          }
          if (subOp[0] == 'O' || subOp[0] == 'X') {
            subRes += oneCnt * zeroCnt;
          }
          res += subRes << (bit + j);
        }
      }
      io::writeInt(res);
      io::writeChar('\n');
    }
  }
}
