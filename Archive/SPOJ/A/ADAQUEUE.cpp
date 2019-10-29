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

#define CAST static_cast

namespace oi {

template <typename T> void readNum(T &res) {
  int ch;
  while ((ch = getchar()) != EOF && !isdigit(ch) && ch != '+' && ch != '-') {
  }
  bool negative = ch == '-';
  res = isdigit(ch) ? ch - '0' : 0;
  while ((ch = getchar()) != EOF && isdigit(ch)) {
    res = (res << 3) + (res << 1) + (ch ^ 48);
  }
  if (negative) {
    res = -res;
  }
}

} // namespace oi

namespace oi {

void readCharArray(char res[]) {
  int ch;
  while ((ch = getchar()) != EOF && isspace(ch)) {
  }
  int idx = 0;
  res[idx++] = CAST<char>(ch);
  while ((ch = getchar()) != EOF && !isspace(ch)) {
    res[idx++] = CAST<char>(ch);
  }
  res[idx] = '\0';
}

} // namespace oi

const int MAXL = 1024;

deque<int> q;
bool rev;
char op[MAXL];

int main() {
  int queryCnt;
  oi::readNum(queryCnt);
  rev = false;
  for (int _ = 0; _ < queryCnt; ++_) {
    oi::readCharArray(op);
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
      oi::readNum(v);
      q.push_back(v);
      break;
    case 't':
      oi::readNum(v);
      q.push_front(v);
      break;
    default:
      assert(false);
      break;
    }
  }
  return 0;
}
