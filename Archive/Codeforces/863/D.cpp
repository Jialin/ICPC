// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, q, m;
  io::readInt(n);
  io::readInt(q);
  io::readInt(m);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  vector<tuple<int, int, int>> ops;
  ops.reserve(q);
  FOR(i, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    ops.emplace_back(op, x - 1, y);
  }
  vector<pair<int, int>> queries;
  queries.reserve(m);
  FOR(i, 0, m) {
    int q;
    io::readInt(q);
    queries.emplace_back(q - 1, i);
  }
  sort(queries.begin(), queries.end());
  for (int i = q - 1; i >= 0; --i) {
    int op, x, y;
    tie(op, x, y) = ops[i];
    if (op == 1) {
      int mediumIdx =
          upper_bound(queries.begin(), queries.end(), make_pair(x, m)) - queries.begin();
      int startIdx;
      for (startIdx = mediumIdx; startIdx > 0 && queries[startIdx - 1].first == x;) {
        queries[--startIdx].first = y - 1;
      }
      int endIdx;
      for (endIdx = mediumIdx; endIdx < m && queries[endIdx].first < y; ++endIdx) {
        --queries[endIdx].first;
      }
      if (startIdx < mediumIdx) {
        reverse(queries.begin() + mediumIdx, queries.begin() + endIdx);
        reverse(queries.begin() + startIdx, queries.begin() + endIdx);
      }
    } else {
      int startIdx = lower_bound(queries.begin(), queries.end(), make_pair(x, 0)) - queries.begin();
      int endIdx;
      int xy_1 = x + y - 1;
      for (endIdx = startIdx; endIdx < m && queries[endIdx].first < y; ++endIdx) {
        queries[endIdx].first = xy_1 - queries[endIdx].first;
      }
      reverse(queries.begin() + startIdx, queries.begin() + endIdx);
    }
  }
  vector<int> results(m);
  FOR(i, 0, m) {
    results[queries[i].second] = vs[queries[i].first];
  }
  FOR(i, 0, m) {
    io::writeInt(results[i]);
    io::writeChar(i + 1 == m ? '\n' : ' ');
  }
  return 0;
}
