#pragma once

using namespace std;

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
