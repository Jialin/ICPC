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

int E, N;

int calc(int x, int y) {
  return x >= 0 && y >= 0 && x + (y << 1) <= E && (x << 1) + y <= N ? x + y : 0;
}

int calcX(int x) {
  return calc(x, min((E - x) >> 1, N - (x << 1)));
}

int calcY(int y) {
  return calc(min(E - (y << 1), (N - y) >> 1), y);
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &E, &N);
    int boundY = ((E << 1) - N) / 3;
    printf("%d\n", max(max(max(max(max(
        calcX(0),
        calcX(1)),
        calcY(0)),
        calcY(1)),
        calcY(boundY)),
        calcY(boundY + 1)));
  }
  return 0;
}
