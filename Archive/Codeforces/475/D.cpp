// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"
#include "math/gcd/gcd32.h"

// Last include
#include "debug/debug.h"

namespace misc {

template<typename K, typename V>
void uniqueMerge(vector<pair<K, V>>& cnts) {
  if (cnts.empty()) {
    return;
  }
  sort(cnts.begin(), cnts.end());
  int i = 0;
  for (int j = 1; j < cnts.size(); ++j) {
    if (cnts[i].first == cnts[j].first) {
      cnts[i].second += cnts[j].second;
    } else {
      swap(cnts[++i], cnts[j]);
    }
  }
  cnts.erase(cnts.begin() + i + 1, cnts.end());
}

} // namespace misc

int main() {
  int n;
  io::readInt(n);
  vector<pair<int, int>> cnts, newCnts;
  unordered_map<int, int64_t> ress;
  FOR(_, 0, n) {
    int newV;
    io::readInt(newV);
    newCnts.clear();
    for (const auto& cnt : cnts) {
      newCnts.emplace_back(math::gcd32(cnt.first, newV), cnt.second);
    }
    newCnts.emplace_back(newV, 1);
    misc::uniqueMerge(newCnts);
    swap(cnts, newCnts);
    for (const auto& [v, cnt] : cnts) {
      ress[v] += cnt;
    }
  }
  int m;
  io::readInt(m);
  FOR(_, 0, m) {
    int v;
    io::readInt(v);
    auto it = ress.find(v);
    io::writeInt(it == ress.end() ? 0 : it->second);
    io::writeChar('\n');
  }
}
