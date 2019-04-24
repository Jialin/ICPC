#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define SIZE(v) (static_cast<int>((v).size()))

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

const int MAXN = 1024 + 1;

int N, B, F;
char S[MAXN];
vector<pair<int, int>> fromRanges[2];
vector<pair<int, int>> toRanges[2];

void firstRound() {
  fromRanges[0].clear();
  for (int i = 0; i < N; i += 16) {
    int j = i;
    char c = '0' + ((i >> 4) & 1);
    for (int k = 0; k < 16 && j < N; ++j, ++k) {
      putchar(c);
    }
    fromRanges[0].emplace_back(i, j - 1);
  }
  putchar('\n');
  fflush(stdout);
  scanf("%s", S);
  int lastIdx = 0;
  toRanges[0].clear();
  FOR(i, 1, N - B + 1) {
    if (i == N - B || S[i] != S[i - 1]) {
      toRanges[0].emplace_back(lastIdx, i - 1);
      lastIdx = i;
    }
    if (i == N - B) break;
  }
  if (toRanges[0].size() < fromRanges[0].size()) {
    toRanges[0].emplace_back(1, 0);
  }
}

void nextRound(int t) {
  fromRanges[t].clear();
  toRanges[t].clear();
  FOR(i, 0, SIZE(fromRanges[t ^ 1])) {
    auto& fromRange = fromRanges[t ^ 1][i];
    auto& toRange = toRanges[t ^ 1][i];
    if (toRange.first > toRange.second || fromRange.first == fromRange.second) {
      FOR(j, fromRange.first, fromRange.second + 1) putchar('0');
      fromRanges[t].push_back(fromRange);
      continue;
    }
    int middle = (fromRange.first + fromRange.second) >> 1;
    FOR(j, fromRange.first, fromRange.second + 1) putchar(j <= middle ? '0' : '1');
    fromRanges[t].emplace_back(fromRange.first, middle);
    fromRanges[t].emplace_back(middle + 1, fromRange.second);
  }
  putchar('\n');
  fflush(stdout);
  scanf("%s", S);
  FOR(i, 0, SIZE(fromRanges[t ^ 1])) {
    auto& fromRange = fromRanges[t ^ 1][i];
    auto& toRange = toRanges[t ^ 1][i];
    if (toRange.first > toRange.second || fromRange.first == fromRange.second) {
      toRanges[t].emplace_back(toRange.first, toRange.second);
      continue;
    }
    int firstOne = toRange.second + 1;
    FOR(j, toRange.first, toRange.second + 1) if (S[j] == '1') {
      firstOne = j;
      break;
    }
    toRanges[t].emplace_back(toRange.first, firstOne - 1);
    toRanges[t].emplace_back(firstOne, toRange.second);
  }
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d%d", &N, &B, &F);
    firstRound();
    int t = 1;
    for (int i = 1; i <= 4; ++i, t ^= 1) nextRound(t);
    t ^= 1;
    bool first = true;
    FOR(i, 0, SIZE(fromRanges[t])) {
      auto& toRange = toRanges[t][i];
      if (toRange.first <= toRange.second) continue;
      auto& fromRange = fromRanges[t][i];
      FOR(j, fromRange.first, fromRange.second + 1) {
        if (!first) putchar(' ');
        first = false;
        printf("%d", j);
      }
    }
    putchar('\n');
    fflush(stdout);
    scanf("%s", S);
  }
  return 0;
}
