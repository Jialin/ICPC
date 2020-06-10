#include <algorithm>
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

using namespace std;

const long long LIMIT = 40000000000000000;

map<long long, long long> fibSums;

int main() {
  fibSums[0] = 0;
  long long a = 0, b = 1, sum = 0;
  while (a <= LIMIT) {
    if (!(a & 1)) {
      sum += a;
      fibSums[a] = sum;
    }
    tie(a, b) = make_pair(b, a + b);
  }
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    long long n;
    scanf("%lld", &n);
    auto it = fibSums.upper_bound(n);
    --it;
    printf("%lld\n", it->second);
  }
  return 0;
}
