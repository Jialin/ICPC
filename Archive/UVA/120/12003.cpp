// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "algo/sqrt_deco/sqrt_deco.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 300000;
const int BLOCK_SIZE = 3500;
const int BLOCK_CNT = MAXN / BLOCK_SIZE + 1;

vector<int> vs;
vector<int> blocks[BLOCK_CNT];

struct SqrtDecoCountLE : algo::SqrtDeco<pair<int, int>, BLOCK_SIZE> {
  using Args = pair<int, int>;

  inline void _handleNode(int idx, Args& args) override {
    if (vs[idx] <= args.second) {
      ++args.first;
    }
  }

  inline void _handleBlock(int blockIdx, Args& args) override {
    const auto& block = blocks[blockIdx];
    args.first += upper_bound(ALL(block), args.second) - block.begin();
  }
};

int main() {
  int n, q, u;
  io::readInt(n);
  io::readInt(q);
  io::readInt(u);
  vs.resize(n);
  for (int i = 0, j = 0, k = 0; i < n; ++i, ++k) {
    if (k == BLOCK_SIZE) {
      k = 0;
      ++j;
    }
    io::readInt(vs[i]);
    blocks[j].push_back(vs[i]);
  }
  for (int i = (n - 1) / BLOCK_SIZE; i >= 0; --i) {
    SORT(blocks[i]);
  }
  pair<int, int> args;
  SqrtDecoCountLE sd;
  FOR(_, 0, q) {
    int lower, upper, threshold, idx;
    io::readInt(lower);
    io::readInt(upper);
    io::readInt(threshold);
    io::readInt(idx);
    --lower;
    args.first = 0;
    args.second = threshold - 1;
    sd.handleRange(lower, upper, args);
    --idx;
    auto& block = blocks[idx / BLOCK_SIZE];
    block.erase(upper_bound(ALL(block), vs[idx]) - 1);
    vs[idx] = CAST<int64_t>(u) * args.first / (upper - lower);
    block.insert(upper_bound(ALL(block), vs[idx]), vs[idx]);
  }
  FOR(i, 0, n) {
    io::writeInt(vs[i]);
    io::writeChar('\n');
  }
  return 0;
}
