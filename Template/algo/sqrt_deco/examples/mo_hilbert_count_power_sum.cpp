// https://codeforces.com/contest/617/problem/E

// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_MO_HILBERT_HANDLE
#define BASE_MO_HILBERT_RESERVE
#include "algo/sqrt_deco/base_mo_hilbert_macros.h"

#include "algo/sqrt_deco/base_mo_hilbert.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXV = 1000000 + 1;

vector<int> vs;
vector<int64_t> results;

struct MoHilbertPowerSumState : algo::BaseMoHilbertState {
  inline MoHilbertPowerSumState() {
    memset(cnts, 0, sizeof(cnts));
  }

  inline void _clear() override {
    FOR(i, lower, upper) {
      --cnts[vs[i]];
    }
    res = 0;
  }

  inline void _initEmptyRange() override {}

  inline void _pushBack(int idx) override {
    int v = vs[idx];
    res += CAST<int64_t>(((cnts[v]++) << 1) | 1) * v;
  }

  inline void _pushFront(int idx) override {
    int v = vs[idx];
    res += CAST<int64_t>(((cnts[v]++) << 1) | 1) * v;
  }

  inline void _popBack(int idx) override {
    int v = vs[idx];
    res -= CAST<int64_t>(((cnts[v]--) << 1) - 1) * v;
  }

  inline void _popFront(int idx) override {
    int v = vs[idx];
    res -= CAST<int64_t>(((cnts[v]--) << 1) - 1) * v;
  }

  inline void _handleQuery(const algo::MoHilbertQuery& query) override {
    results[query.idx] = res;
  }

  int cnts[MAXV];
  int64_t res;
};

const int RANGE_BIT = 18;

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vs.resize(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  results.resize(q);
  algo::MoHilbert<MoHilbertPowerSumState, RANGE_BIT> mo;
  mo.reserve(q);
  FOR(i, 0, q) {
    int lower, upper;
    io::readInt(lower);
    io::readInt(upper);
    mo.addQuery(lower - 1, upper, i);
  }
  mo.handle();
  FOR(i, 0, q) {
    io::writeInt(results[i]);
    io::writeChar('\n');
  }
  return 0;
}
