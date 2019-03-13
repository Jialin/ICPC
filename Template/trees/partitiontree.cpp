namespace trees { namespace pt {

template<typename T>
class PartitionTree {
  int n;
  vector<T> sortedVs;
  vector<vector<T>> vs;
  vector<vector<int>> goLeftSum;

  inline void build(int depth, int fromIdx, int toIdx) {
    if (fromIdx > toIdx) return;
    int mediumIdx = (fromIdx + toIdx) >> 1, mediumV = sortedVs[mediumIdx];
    const auto& goLeftSumBegin = goLeftSum[depth].begin();
    fill(goLeftSumBegin + fromIdx, goLeftSumBegin + toIdx + 1, 0);
    int leftCnt = mediumIdx - fromIdx + 1;
    for (int i = fromIdx; i <= toIdx; ++i) if (vs[depth][i] < mediumV) {
      goLeftSum[depth][i] = 1;
      --leftCnt;
    }
    for (int i = fromIdx; i <= toIdx && leftCnt > 0; ++i) if (vs[depth][i] == mediumV) {
      goLeftSum[depth][i] = 1;
      --leftCnt;
    }
    int leftPnt = fromIdx, rightPnt = mediumIdx + 1;
    for (int i = fromIdx; i <= toIdx; ++i) {
      int j = goLeftSum[depth][i] > 0 ? leftPnt++ : rightPnt++;
      vs[depth + 1][j] = vs[depth][i];
      if (i > fromIdx) goLeftSum[depth][i] += goLeftSum[depth][i - 1];
    }
    if (fromIdx < mediumIdx) {
      build(depth + 1, fromIdx, mediumIdx);
      build(depth + 1, mediumIdx + 1, toIdx);
    }
  }

public:
  // Initializes
  inline void init(int _n, const T* _vs) {
    n = _n;
    int bit = 33 - __builtin_clz(n);
    vs.resize(bit);
    goLeftSum.resize(bit);
    sortedVs.resize(n);
    for (int i = 0; i < bit; ++i) {
      vs[i].resize(n);
      goLeftSum[i].resize(n);
    }
    for (int i = 0; i < n; ++i) sortedVs[i] = vs[0][i] = _vs[i];
    sort(sortedVs.begin(), sortedVs.end());
    build(0, 0, n - 1);
  }

  // Counts the number of elements which is less than value in the given range.
  inline int cntLess(int fromIdx, int toIdx, T v) {
    int res = 0;
    int depth = 0, lower = 0, upper = n - 1;
    for ( ; lower < upper && fromIdx <= toIdx; ++depth) {
      int medium = (lower + upper) >> 1;
      int subGoLeftCnt = fromIdx == lower ? 0 : goLeftSum[depth][fromIdx - 1];
      int totGoLeftCnt = goLeftSum[depth][toIdx];
      if (sortedVs[medium] < v) {
        fromIdx += medium - lower - subGoLeftCnt + 1;
        toIdx += medium - lower - totGoLeftCnt + 1;
        lower = medium + 1;
        res += totGoLeftCnt - subGoLeftCnt;
      } else {
        fromIdx = lower + subGoLeftCnt;
        toIdx = lower + totGoLeftCnt - 1;
        upper = medium;
      }
    }
    return fromIdx <= toIdx && vs[depth][lower] < v ? res + 1 : res;
  }
}; // class PartitionTree
}} // namespace trees::pt
