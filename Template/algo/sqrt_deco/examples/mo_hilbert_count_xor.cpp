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

const int RANGE_BIT = 20;
const int MAXV = 1 << RANGE_BIT;

vector<int> pXorSum;
vector<int64_t> results;
int target;

struct MoHilbertCountXorState : algo::BaseMoHilbertState {
  inline MoHilbertCountXorState() {
    memset(cnts, 0, sizeof(cnts));
  }

  inline void _clear() override {
    FOR(i, lower, upper + 1) {
      --cnts[pXorSum[i]];
    }
    res = 0;
  }

  inline void _initEmptyRange() override {
    ++cnts[pXorSum[lower]];
    res = 0;
  }

  inline void _pushBack(int idx) override {
    int v = pXorSum[idx + 1];
    res += cnts[v ^ target];
    ++cnts[v];
  }

  inline void _pushFront(int idx) override {
    int v = pXorSum[idx];
    res += cnts[v ^ target];
    ++cnts[v];
  }

  inline void _popBack(int idx) override {
    int v = pXorSum[idx + 1];
    --cnts[v];
    res -= cnts[v ^ target];
  }

  inline void _popFront(int idx) override {
    int v = pXorSum[idx];
    --cnts[v];
    res -= cnts[v ^ target];
  }

  inline void _handleQuery(const algo::MoHilbertQuery& query) override {
    results[query.idx] = res;
  }

  int cnts[MAXV];
  int64_t res;
};

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  io::readInt(target);
  pXorSum.resize(n + 1);
  FOR(i, 0, n) {
    io::readInt(pXorSum[i + 1]);
    pXorSum[i + 1] ^= pXorSum[i];
  }
  results.resize(q);
  algo::MoHilbert<MoHilbertCountXorState, RANGE_BIT> mo;
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
