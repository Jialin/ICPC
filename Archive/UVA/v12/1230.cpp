#include <cassert>
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
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d\n", math::expMod(a, b, c));
  }
  return 0;
}
