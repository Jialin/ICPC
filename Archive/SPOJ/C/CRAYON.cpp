// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

char op[2];

int main() {
  int q;
  io::readInt(q);
  vector<tuple<char, int, int>> queries;
  queries.reserve(q);
  vector<int> addIdxs;
  addIdxs.reserve(q);
  vector<int> disLower;
  disLower.reserve(q);
  vector<int> disUpper;
  disUpper.reserve(q);
  FOR(i, 0, q) {
    io::readCharArray(op);
    int lower, upper;
    if (op[0] == 'D') {
      io::readInt(lower);
      io::readInt(upper);
      disLower.push_back(lower);
      disUpper.push_back(upper);
      addIdxs.push_back(i);
    } else if (op[0] == 'C') {
      int idx;
      io::readInt(idx);
      idx = addIdxs[idx - 1];
      lower = get<1>(queries[idx]);
      upper = get<2>(queries[idx]);
    } else {
      io::readInt(lower);
      io::readInt(upper);
    }
    queries.emplace_back(op[0], lower, upper);
  }
  SORTUNIQUE(disLower);
  SORTUNIQUE(disUpper);
  ds::FenwickSum<int> fenLower;
  fenLower.init(SIZE(disLower));
  ds::FenwickSum<int> fenUpper;
  fenUpper.init(SIZE(disUpper));
  for (auto [op, lower, upper] : queries) {
    if (op == 'D') {
      fenLower.update(INDEX(disLower, lower), 1);
      fenUpper.update(INDEX(disUpper, upper), 1);
    } else if (op == 'C') {
      fenLower.update(INDEX(disLower, lower), -1);
      fenUpper.update(INDEX(disUpper, upper), -1);
    } else {
      int idx1 = INDEX(disLower, upper + 1);
      --idx1;
      int idx2 = INDEX(disUpper, lower);
      --idx2;
      io::writeInt(max(
          (idx1 >= 0 ? fenLower.calcPrefix(idx1) : 0) - (idx2 >= 0 ? fenUpper.calcPrefix(idx2) : 0),
          0));
      io::writeChar('\n');
    }
  }
}
