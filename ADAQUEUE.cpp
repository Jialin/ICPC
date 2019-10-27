#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

const int MAXL = 1024;

deque<int> q;
bool rev;
char op[MAXL];

int main() {
  int queryCnt;
  scanf("%d", &queryCnt);
  rev = false;
  for (int _ = 0; _ < queryCnt; ++_) {
    scanf("%s", op);
    char c = op[0];
    int v;
    if (rev) {
      if (c == 'b' || c == 'f') {
        c ^= 'b' ^ 'f';
      } else if (c == 'p' || c == 't') {
        c ^= 'p' ^ 't';
      }
    }
    switch (c) {
    case 'b':
      if (q.empty()) {
        puts("No job for Ada?");
      } else {
        printf("%d\n", q.back());
        q.pop_back();
      }
      break;
    case 'f':
      if (q.empty()) {
        puts("No job for Ada?");
      } else {
        printf("%d\n", q.front());
        q.pop_front();
      }
      break;
    case 'r':
      rev = !rev;
      break;
    case 'p':
      scanf("%d", &v);
      q.push_back(v);
      break;
    case 't':
      scanf("%d", &v);
      q.push_front(v);
      break;
    default:
      assert(false);
      break;
    }
  }
  return 0;
}
