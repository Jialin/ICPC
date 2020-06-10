#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

const long long LIMIT = 10000000000;

unordered_set<long long> fibs;

int main() {
  fibs.emplace(0);
  long long a = 0, b = 1;
  while (a < LIMIT) {
    tie(a, b) = make_pair(b, a + b);
    fibs.emplace(a);
  }
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    long long n;
    scanf("%lld", &n);
    puts(fibs.count(n) ? "IsFibo" : "IsNotFibo");
  }
  return 0;
}
