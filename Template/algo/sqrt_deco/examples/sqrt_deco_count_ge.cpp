// https://www.spoj.com/problems/GIVEAWAY/

// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "algo/sqrt_deco/base_sqrt_deco.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 500000;
const int BLOCK_SIZE = 2000;
const int BLOCK_CNT = MAXN / BLOCK_SIZE + 1;

vector<int> vs;
vector<int> blocks[BLOCK_CNT];

struct SqrtDecoCountGE : algo::BaseSqrtDeco<pair<int, int>, BLOCK_SIZE> {
  using Args = pair<int, int>;

  inline void _handleNode(int idx, Args& args) override {
    if (vs[idx] >= args.second) {
      ++args.first;
    }
  }

  inline void _handleBlock(int blockIdx, Args& args) override {
    const auto& block = blocks[blockIdx];
    args.first += block.end() - lower_bound(ALL(block), args.second);
  }
};

int main() {
  int n;
  io::readInt(n);
  vs.resize(n);
  for (int i = 0, j = 0, k = 0; i < n; ++i, ++k) {
    if (k == BLOCK_SIZE) {
      ++j;
      k = 0;
    }
    io::readInt(vs[i]);
    blocks[j].push_back(vs[i]);
  }
  for (int i = (n - 1) / BLOCK_SIZE; i >= 0; --i) {
    SORT(blocks[i]);
  }
  int q;
  io::readInt(q);
  SqrtDecoCountGE sd;
  pair<int, int> args;
  FOR(_, 0, q) {
    int op, a, b;
    io::readInt(op);
    io::readInt(a);
    io::readInt(b);
    --a;
    if (op) {
      auto& block = blocks[a / BLOCK_SIZE];
      block.erase(upper_bound(ALL(block), vs[a]) - 1);
      block.insert(upper_bound(ALL(block), b), b);
      vs[a] = b;
    } else {
      int c;
      io::readInt(c);
      args.first = 0;
      args.second = c;
      sd.handleRange(a, b, args);
      io::writeInt(args.first);
      io::writeChar('\n');
    }
  }
  return 0;
}
