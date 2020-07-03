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
#include "math/prime/prime_iterator.h"

using namespace std;

const int MAXV = 10527449;
const int MAXPV = (MAXV >> 1) + 1;
const int MAXQ = 1000;

math::PrimeIterator pi(MAXPV);
vector<int> primes;
vector<bool> isValid;
vector<pair<int, int>> queries;
int answers[MAXQ];

int main() {
  primes.reserve(365560);
  pi.iterate(MAXPV, [](int p) { primes.push_back(p); });
  isValid.assign(MAXV + 1, false);
  for (size_t i = 0; i < primes.size() && primes[i] <= MAXV / primes[i]; ++i) {
    for (size_t j = i + 1; j < primes.size(); ++j) {
      int v = primes[i] * primes[j];
      if (v > MAXV) {
        break;
      }
      isValid[v] = true;
    }
  }
  int taskNumber;
  io::readInt(taskNumber);
  queries.resize(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    auto& query = queries[taskIdx];
    query.second = taskIdx;
    io::readInt(query.first);
  }
  sort(queries.begin(), queries.end());
  int cnt = 0, pnt = 0;
  for (const auto& query : queries) {
    for (; cnt < query.first; ++pnt) {
      if (isValid[pnt]) {
        ++cnt;
      }
    }
    answers[query.second] = pnt - 1;
  }
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::writeInt(answers[taskIdx]);
    io::writeChar('\n');
  }
  return 0;
}
