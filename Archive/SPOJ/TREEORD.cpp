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

int n;
vector<int> pre;
vector<int> post;
vector<int> in;
unordered_map<int, int> idxLookup;

inline bool isValid(int preFrom, int preTo, int postFrom, int postTo, int inFrom, int inTo) {
  int length = preTo - preFrom + 1;
  if (length == 0) return true;
  if (length == 1) {
    return pre[preFrom] == post[postFrom]
        && pre[preFrom] == in[inFrom];
  }
  if (pre[preFrom] != post[postTo]) return false;
  int idx = idxLookup[pre[preFrom]];
  if (idx < inFrom || inTo < idx) return false;
  int leftCnt = idx - inFrom;
  int rightCnt = inTo - idx;
  return isValid(preFrom + 1, preFrom + leftCnt, postFrom, postFrom + leftCnt - 1, inFrom, inFrom + leftCnt - 1)
      && isValid(preTo - rightCnt + 1, preTo, postTo - rightCnt, postTo - 1, inTo - rightCnt + 1, inTo);
}

int main() {
  scanf("%d", &n);
  pre.resize(n); FOR(i, 0, n) scanf("%d", &pre[i]);
  post.resize(n); FOR(i, 0, n) scanf("%d", &post[i]);
  in.resize(n);
  FOR(i, 0, n) {
    scanf("%d", &in[i]);
    idxLookup[in[i]] = i;
  }
  puts(isValid(0, n - 1, 0, n - 1, 0, n - 1) ? "yes" : "no");
  return 0;
}
