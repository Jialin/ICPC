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

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

const int MAXN = 50000;

int n;
char path[MAXN << 1];

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%s", &n, path);
    n = (n << 1) - 2;
    printf("Case #%d: ", taskIdx);
    FOR(i, 0, n) putchar(path[i] ^ 'E' ^ 'S');
    putchar('\n');
  }
  return 0;
}
