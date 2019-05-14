#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define CAST static_cast
#define SIZE(v) (CAST<int>((v).size()))
#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

int n;
vector<string> ps, newPS;
vector<char> answer;
char token[1024];

char calcMove(const string& p, int day) {
  return p[day % SIZE(p)];
}

void nextPS(int day, char keep) {
  newPS.clear();
  for (const auto& p : ps) if (calcMove(p, day) == keep) {
    newPS.push_back(p);
  }
  answer.push_back(keep);
}

bool calc() {
  answer.clear();
  for (int day = 0; ; ++day) {
    bool isR = false;
    bool isP = false;
    bool isS = false;
    for (const auto& p : ps) {
      switch (calcMove(p, day)) {
      case 'R':
        isR = true;
        break;
      case 'P':
        isP = true;
        break;
      case 'S':
        isS = true;
        break;
      }
    }
    if (isR && isP && isS) return false;
    if (isR && isP) {
      nextPS(day, 'P');
    } else if (isR && isS) {
      nextPS(day, 'R');
    } else if (isP && isS) {
      nextPS(day, 'S');
    } else {
      if (isR) {
        answer.push_back('P');
      } else if (isP) {
        answer.push_back('S');
      } else if (isS) {
        answer.push_back('R');
      } else {
        assert(false);
      }
      return true;
    }
    ps.swap(newPS);
  }
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d", &n);
    ps.resize(n);
    FOR(i, 0, n) {
      scanf("%s", token);
      ps[i] = token;
    }
    bool res = calc();
    printf("Case #%d: ", taskIdx);
    if (res) {
      for (char c : answer) putchar(c);
      putchar('\n');
    } else {
      puts("IMPOSSIBLE");
    }
  }
  return 0;
}
