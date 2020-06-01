#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "math/gcd.h"

using namespace std;

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int x, y;
    scanf("%d%d", &x, &y);
    int gcd = math::gcd(x, y);
    printf("%d %lld\n", gcd, static_cast<int64_t>(x) / gcd * y);
  }
  return 0;
}
