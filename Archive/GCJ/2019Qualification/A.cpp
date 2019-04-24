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

int length;
char n[101];

bool contains4() {
  FOR(i, 0, length) if (n[i] == '4') {
    return true;
  }
  return false;
}

void substract(int v) {
  for (int i = length - 1; i >= 0 && v; --i) {
    int digit = n[i] - '0';
    if (digit >= v) {
      digit -= v;
      v = 0;
    } else {
      digit = digit + 10 - v;
      v = 1;
    }
    n[i] = static_cast<char>('0' + digit);
  }
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%s", n);
    length = static_cast<int>(strlen(n));
    printf("Case #%d: ", taskIdx);
    if (contains4()) {
      FOR(i, 0, length) {
        putchar(n[i] == '4' ? '3' : n[i]);
      }
      putchar(' ');
      bool begin = false;
      FOR(i, 0, length) {
        if (n[i] == '4') {
          begin = true;
          putchar('1');
        } else if (begin) {
          putchar('0');
        }
      }
    } else {
      int v = n[length - 1] == '5' ? 2 : 1;
      putchar(static_cast<char>('0' + v));
      putchar(' ');
      substract(v);
      bool begin = false;
      FOR(i, 0, length) {
        if (n[i] != '0') begin = true;
        if (begin) putchar(n[i]);
      }
    }
    putchar('\n');
  }
  return 0;
}

