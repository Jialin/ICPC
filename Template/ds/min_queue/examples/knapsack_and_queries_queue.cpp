// https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_d
#include "common/macros.h"
#include "ds/min_queue/base_min_queue.h"
#include "ds/sliding_window/max_sliding_window.h"

const int64_t MINF = -10000000000000000LL;

int mod, l, r;
ds::MaxSlidingWindow<int64_t> _msw;

struct KnapsackAndQueriesQueue : ds::BaseMinQueue<pair<int, int>, vector<int64_t>, int64_t> {
  inline void addToStack(
      vector<pair<pair<int, int>, vector<int64_t>>>& stack,
      pair<pair<int, int>, vector<int64_t>>&& dirtyValue) const override {
    int weight = dirtyValue.first.first % mod;
    int value = dirtyValue.first.second;
    auto& dp = dirtyValue.second;
    FILL(dp, MINF);
    if (stack.empty()) {
      dp[0] = 0;
      dp[weight] = value;
    } else {
      const auto& prevDp = stack.back().second;
      int j = weight;
      FOR(i, 0, mod) {
        dp[j] = max(prevDp[j], prevDp[i] + value);
        j = j + 1 == mod ? 0 : j + 1;
      }
    }
    stack.push_back(std::move(dirtyValue));
  }

  inline void calcEmpty(int64_t& res) const override {
    res = l == 0 ? 0 : -1;
  }

  inline void calcTailStackOnly(
      const pair<pair<int, int>, vector<int64_t>>& tailValue, int64_t& res) const override {
    res = *max_element(tailValue.second.begin() + l, tailValue.second.begin() + r + 1);
  }

  inline void calcHeadStackOnly(
      const pair<pair<int, int>, vector<int64_t>>& headValue, int64_t& res) const override {
    res = *max_element(headValue.second.begin() + l, headValue.second.begin() + r + 1);
  }

  inline void combine(
      const pair<pair<int, int>, vector<int64_t>>& headValue,
      const pair<pair<int, int>, vector<int64_t>>& tailValue,
      int64_t& res) const override {
    res = -1;
    _msw.init(r - l + 1);
    int idx = 0;
    for (int i = r; i > l; --i) {
      _msw.push_back(idx++, tailValue.second[i]);
    }
    int j = l;
    FOR(i, 0, mod) {
      _msw.push_back(idx++, tailValue.second[j]);
      j = j ? j - 1 : mod - 1;
      res = max(res, headValue.second[i] + _msw.get().second);
    }
  }
};
