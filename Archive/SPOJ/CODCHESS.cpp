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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define SIZE(v) (static_cast<int>((v).size()))

#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)

#define FOR(i,l,r) for(int i=(l);i<(r);++i)



int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n; scanf("%d", &n);
    printf("%d\n", 1 - (n & 1));
  }
  return 0;
}
