// https://www.spoj.com/problems/DQUERY/ : use fenwick tree is a better solution

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

vector<int> prevs, nexts, results;

struct MoHilbertCountDistinctState : algo::BaseMoHilbertState {
  inline MoHilbertCountDistinctState() {
    res = 0;
  }

  inline void _clear() override {
    FOR(i, lower, upper) {
      _popFront(i);
    }
  }

  inline void _initEmptyRange() override {}

  inline void _pushBack(int idx) override {
    if (prevs[idx] < lower) {
      ++res;
    }
  }

  inline void _pushFront(int idx) override {
    if (upper <= nexts[idx]) {
      ++res;
    }
  }

  inline void _popBack(int idx) override {
    if (prevs[idx] < lower) {
      --res;
    }
  }

  inline void _popFront(int idx) override {
    if (upper <= nexts[idx]) {
      --res;
    }
  }

  inline void _handleQuery(const algo::MoHilbertQuery& query) override {
    results[query.idx] = res;
  }

  int res;
};

const int MAXV = 1000000 + 1;

int lastPs[MAXV];

int main() {
  memset(lastPs, 0xFF, sizeof(lastPs));
  int n;
  io::readInt(n);
  prevs.assign(n, -1);
  nexts.assign(n, n);
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    if (lastPs[v] >= 0) {
      nexts[lastPs[v]] = i;
      prevs[i] = lastPs[v];
    }
    lastPs[v] = i;
  }
  algo::MoHilbert<MoHilbertCountDistinctState, 15> mo;
  int q;
  io::readInt(q);
  results.resize(q);
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
