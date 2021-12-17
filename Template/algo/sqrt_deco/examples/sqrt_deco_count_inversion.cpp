// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141

// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "algo/sqrt_deco/base_sqrt_deco.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000;
const int BLOCK_SIZE = 300;
const int BLOCK_CNT = MAXN / BLOCK_SIZE + 1;

vector<int> vs;
vector<int> blocks[BLOCK_CNT];
vector<bool> covered;

struct SqrtDecoCountInversionArgs {
  bool gt;
  int cnt, threshold;
};

struct SqrtDecoCountInversion : algo::BaseSqrtDeco<SqrtDecoCountInversionArgs, BLOCK_SIZE> {
  using Args = SqrtDecoCountInversionArgs;

  inline void _handleNode(int idx, Args& args) override {
    if (covered[idx]) {
      return;
    }
    if (args.gt) {
      if (vs[idx] > args.threshold) {
        ++args.cnt;
      }
    } else {
      if (vs[idx] < args.threshold) {
        ++args.cnt;
      }
    }
  }

  inline void _handleBlock(int blockIdx, Args& args) override {
    const auto& block = blocks[blockIdx];
    if (args.gt) {
      args.cnt += block.end() - upper_bound(ALL(block), args.threshold);
    } else {
      args.cnt += INDEX(block, args.threshold);
    }
  }
};

const int MAXQ = 100000;

int main() {
  int n, q;
  vector<int> lookup;
  lookup.reserve(MAXN);
  vector<int> idxs;
  idxs.reserve(MAXQ);
  vector<int64_t> results;
  results.reserve(MAXQ);
  SqrtDecoCountInversion sd;
  SqrtDecoCountInversionArgs args;
  while (io::readInt(n)) {
    io::readInt(q);
    vs.resize(n);
    lookup.resize(n);
    FOR(i, 0, n) {
      io::readInt(vs[i]);
      lookup[--vs[i]] = i;
    }
    covered.assign(n, false);
    idxs.resize(q);
    FOR(i, 0, q) {
      io::readInt(idxs[i]);
      --idxs[i];
      idxs[i] = lookup[idxs[i]];
      covered[idxs[i]] = true;
    }
    for (int i = (n - 1) / BLOCK_SIZE; i >= 0; --i) {
      blocks[i].clear();
    }
    for (int i = 0, j = 0, k = 0; i < n; ++i, ++k) {
      if (k == BLOCK_SIZE) {
        k = 0;
        ++j;
      }
      if (!covered[i]) {
        blocks[j].push_back(vs[i]);
      }
    }
    for (int i = (n - 1) / BLOCK_SIZE; i >= 0; --i) {
      SORT(blocks[i]);
    }
    int64_t res = 0;
    for (int i = 0, j = 0, k = 0; i < n; ++i, ++k) {
      if (k == BLOCK_SIZE) {
        k = 0;
        ++j;
      }
      if (covered[i]) {
        continue;
      }
      args.threshold = vs[i];
      args.cnt = 0;
      args.gt = true;
      sd.handleRange(0, i, args);
      res += args.cnt;
    }
    results.resize(q);
    for (int i = q - 1; i >= 0; --i) {
      int j = idxs[i];
      int v = vs[j];
      args.threshold = v;
      args.cnt = 0;

      args.gt = true;
      sd.handleRange(0, j, args);
      args.gt = false;
      sd.handleRange(j + 1, n, args);

      res += args.cnt;

      results[i] = res;
      covered[j] = false;
      auto& block = blocks[j / BLOCK_SIZE];
      block.insert(upper_bound(ALL(block), v), v);
    }
    FOR(i, 0, q) {
      io::writeInt(results[i]);
      io::writeChar('\n');
    }
  }
  return 0;
}
