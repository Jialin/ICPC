// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_MIN_QUEUE_RESERVE

#include "ds/min_queue/base_min_queue.h"
#include "ds/min_queue/base_min_queue_macros.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"
#include "math/mod/add.h"
#include "math/mod/mul.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000007;

int n, q;
int fromIdx, toIdx, res;

struct BinaryLandQueue : ds::BaseMinQueue<int, vector<vector<int>>, int> {
  inline void addToStack(
      vector<pair<int, vector<vector<int>>>>& stack,
      pair<int, vector<vector<int>>>&& dirtyValue) const override {
    const auto& update = dirtyValue.first;
    auto& vs = dirtyValue.second;
    FOR(i, 0, n) FOR(j, 0, n) {
      vs[i][j] = 0;
    }
    if (stack.empty()) {
      FOR(i, 0, n) {
        vs[i][i] = 1;
      }
    } else {
      FOR(i, 0, n) {
        int bound = min(i + 1, n - 1);
        const auto& prevUpdate = stack.back().first;
        const auto& prevVs = stack.back().second;
        FORIF(j, max(i - 1, 0), bound + 1, ((update >> i) & 1) == ((prevUpdate >> j) & 1)) {
          FOR(k, 0, n) {
            vs[i][k] = math::addMod(vs[i][k], prevVs[j][k], MOD);
          }
        }
      }
    }
    stack.push_back(std::move(dirtyValue));
  }

  inline void calcEmpty(int& res) const override {
    res = 0;
  }

  inline void
  calcTailStackOnly(const pair<int, vector<vector<int>>>& tailValue, int& res) const override {
    res = tailValue.second[toIdx][fromIdx];
  }

  inline void
  calcHeadStackOnly(const pair<int, vector<vector<int>>>& headValue, int& res) const override {
    res = headValue.second[fromIdx][toIdx];
  }

  inline void combine(
      const pair<int, vector<vector<int>>>& headValue,
      const pair<int, vector<vector<int>>>& tailValue,
      int& res) const override {
    res = 0;
    const auto& headUpdate = headValue.first;
    const auto& tailUpdate = tailValue.first;
    if (((headUpdate >> fromIdx) & 1) != ((tailUpdate >> toIdx) & 1)) {
      return;
    }
    const auto& headVs = headValue.second;
    const auto& tailVs = tailValue.second;
    FOR(i, 0, n) {
      int bound = min(i + 1, n - 1);
      FOR(j, max(i - 1, 0), bound + 1) {
        res = math::addMod(res, math::mulMod(headVs[fromIdx][i], tailVs[toIdx][j], MOD), MOD);
      }
    }
  }
};

char op[8], update[32];
BinaryLandQueue blq;

int main() {
  io::readInt(n);
  io::readInt(q);
  blq.reserve(q);
  FOR(_, 0, q) {
    io::readCharArray(op);
    if (op[0] == 'a') {
      io::readCharArray(update);
      int mask = 0;
      FORIF(i, 0, n, update[i] == '1') {
        mask |= 1 << i;
      }
      pair<int, vector<vector<int>>> value{mask, vector<vector<int>>(n, vector<int>(n))};
      blq.push_back(std::move(value));
    } else if (op[0] == 'r') {
      blq.pop_front();
    } else {
      io::readInt(fromIdx);
      io::readInt(toIdx);
      --fromIdx;
      --toIdx;
      int res;
      blq.calc(res);
      io::writeInt(res);
      io::writeChar('\n');
    }
  }
}
