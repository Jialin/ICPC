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

#define BIGINT_ASSIGN_INT
#define BIGINT_DIGIT_SUM
#define BIGINT_MUL_INLINE_INT
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "math/bigint/bigint.h"

const int MAXN = 1001;

int answers[MAXN];
math::BigInt<> fact;

int main() {
  fact = 1;
  answers[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    fact *= i;
    answers[i] = fact.digitSum();
  }
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    scanf("%d", &n);
    printf("%d\n", answers[n]);
  }
  return 0;
}
