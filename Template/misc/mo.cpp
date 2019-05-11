namespace misc {

using TIII = tuple<int, int, int>;

/** Mo's algorithm, which process range queries in O(range * sqrt(range) + queries * log(queries)). */
inline void mo(
    vector<TIII>& queries,
    const function<void(int)> addProcessor,
    const function<void(int)> removeProcessor,
    const function<void(int)> queryProcessor) {

  if (queries.empty()) return;
  int lower = INT_MAX, upper = INT_MIN;
  for (const auto& query : queries) {
    lower = min(lower, get<0>(query));
    upper = max(upper, get<1>(query));
  }
  int bucket = max(1, CAST<int>(sqrt(upper - lower)));
  sort(queries.begin(), queries.end(), [&lower, &bucket](const TIII& lhs, const TIII& rhs) {
    int lIdx = (get<0>(lhs) - lower) / bucket;
    int rIdx = (get<0>(rhs) - lower) / bucket;
    return lIdx != rIdx ? lIdx < rIdx : get<1>(lhs) < get<1>(rhs);
  });
  bool first = true;
  for (const auto& query : queries) {
    int nxtLower, nxtUpper, idx;
    tie(nxtLower, nxtUpper, idx) = query;
    if (first) {
      first = false;
      for (int i = nxtLower; i < nxtUpper; ++i) addProcessor(i);
    } else {
      for (int i = upper - 1; i >= nxtUpper; --i) removeProcessor(i);
      for (int i = upper; i < nxtUpper; ++i) addProcessor(i);
      for (int i = lower - 1; i >= nxtLower; --i) addProcessor(i);
      for (int i = lower; i < nxtLower; ++i) removeProcessor(i);
    }
    lower = nxtLower;
    upper = nxtUpper;
    queryProcessor(idx);
  }
}
} // namespace misc
