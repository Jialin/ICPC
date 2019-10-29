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

inline int calc(int n) {
  if (n < 3) return n;
  int cnt;
  for (cnt = 0; !(n & 1); ++cnt, n >>= 1) {}
  return cnt << 1;
}

int main() {
  int n; scanf("%d", &n);
  printf("%d\n", calc(n));
  return 0;
}
