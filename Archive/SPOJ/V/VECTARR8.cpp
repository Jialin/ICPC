#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/prime/prime_checker.h"

using namespace std;

const int POW10[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

struct Query {
  int n, idx;

  inline Query(int idx_) {
    idx = idx_;
    io::readInt(n);
  }
};

const int MAXN = 100000;

int answers[MAXN];

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  vector<Query> queries;
  queries.reserve(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    queries.push_back(Query(taskIdx));
  }
  sort(queries.begin(), queries.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.n < rhs.n;
  });
  int maxN = max(queries.back().n, 10);
  math::PrimeChecker pc(maxN);
  vector<bool> isValid;
  isValid.assign((maxN + 1) >> 1, false);
  for (int i = 3; i < 10; ++i) {
    if (pc.isPrime(i)) {
      isValid[i >> 1] = true;
    }
  }
  for (int len = 1; len < 7; ++len) {
    for (int digit = 1, startV = POW10[len]; digit < 10;
         ++digit, startV += POW10[len]) {
      int i = POW10[len - 1];
      int v = startV + i;
      if (!(v & 1)) {
        ++i;
        ++v;
      }
      for (; i < POW10[len] && v <= maxN; i += 2, v += 2) {
        isValid[v >> 1] = isValid[i >> 1] && pc.isPrime(v);
      }
    }
  }
  int lastN = 1, cnt = 0;
  for (auto& query : queries) {
    for (; lastN <= query.n; ++lastN) {
      if (lastN == 2 || ((lastN & 1) && isValid[lastN >> 1])) {
        ++cnt;
      }
    }
    answers[query.idx] = cnt;
  }
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::writeInt(answers[taskIdx]);
    io::writeChar('\n');
  }
  return 0;
}
