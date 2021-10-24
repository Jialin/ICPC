// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_MIN_QUEUE_RESERVE

#include "ds/min_queue/base_min_queue.h"
#include "ds/sliding_window/max_sliding_window.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

class Crypto {
public:
  Crypto() {
    sm = cnt = 0;
    seed();
  }

  int decode(int z) {
    z ^= next();
    z ^= (next() << 8);
    z ^= (next() << 16);
    z ^= (next() << 22);
    return z;
  }

  void query(long long z) {
    const long long B = 425481007;
    const long long MD = 1000000007;
    cnt++;
    sm = ((sm * B % MD + z) % MD + MD) % MD;
    seed();
  }

private:
  long long sm;
  int cnt;

  uint8_t data[256];
  int I, J;

  void swap_data(int i, int j) {
    uint8_t tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
  }

  void seed() {
    uint8_t key[8];
    for (int i = 0; i < 4; i++) {
      key[i] = (sm >> (i * 8));
    }
    for (int i = 0; i < 4; i++) {
      key[i + 4] = (cnt >> (i * 8));
    }

    for (int i = 0; i < 256; i++) {
      data[i] = i;
    }
    I = J = 0;

    int j = 0;
    for (int i = 0; i < 256; i++) {
      j = (j + data[i] + key[i % 8]) % 256;
      swap_data(i, j);
    }
  }

  uint8_t next() {
    I = (I + 1) % 256;
    J = (J + data[I]) % 256;
    swap_data(I, J);
    return data[(data[I] + data[J]) % 256];
  }
};

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

KnapsackAndQueriesQueue kaqq;

int main() {
  int q;
  io::readInt(mod);
  io::readInt(q);
  kaqq.reserve(q);
  Crypto c;
  for (int i = 0; i < q; i++) {
    int t, w, v;
    io::readInt(t);
    io::readInt(w);
    io::readInt(v);
    io::readInt(l);
    io::readInt(r);
    t = c.decode(t);
    w = c.decode(w);
    v = c.decode(v);
    l = c.decode(l);
    r = c.decode(r);
    if (t == 1) {
      kaqq.push_back({{w, v}, vector<int64_t>(mod)});
    } else {
      kaqq.pop_front();
    }
    int64_t res;
    kaqq.calc(res);
    if (res < 0) {
      res = -1;
    }
    c.query(res);
    io::writeInt(res);
    io::writeChar('\n');
  }
}
