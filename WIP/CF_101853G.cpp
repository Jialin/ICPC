#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#include "debug/debug.h"
#include "math/mod/log.h"

math::LogMod<> logMod(100003);

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int a, b, mod;
    scanf("%d%d%d", &a, &b, &mod);
    int res;
    if (a > 0) {
      logMod.calc(a, b, mod, res);
    } else {
      res = 1;
    }
    printf("%d\n", res);
  }
  return 0;
}
