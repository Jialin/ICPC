#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "math/mod_operators/exp.h"

using namespace std;

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, k;
    scanf("%d%d", &n, &k);
    long double lognk = log10(static_cast<long double>(n)) * k;
    lognk -= static_cast<int>(lognk);
    printf("%d...%03d\n", static_cast<int>(pow(10, lognk) * 100),
           math::expMod(n, k, 1000));
  }
  return 0;
}
