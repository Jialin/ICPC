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

#include "collections/unique_counter.h"
#include "math/pow10.h"
#include "math/prime/phi_all.h"

const int MAXDIGIT = 7;
const int BOUND = math::POW10[MAXDIGIT + 1];

math::PhiAll phiAll(BOUND);
collections::UniqueCounter counter(10, 10);
vector<int> answers;

inline void updateCounter(int n, int delta) {
  for (; n > 0; n /= 10) {
    counter.update(n % 10, delta);
  }
}

int main() {
  int num = 1, den = 0;
  for (int digit = 2; digit <= MAXDIGIT; ++digit) {
    for (int n = math::POW10[digit - 1]; n < math::POW10[digit]; ++n) {
      int phi = phiAll.get(n);
      if (phi < math::POW10[digit - 1]) {
        continue;
      }
      counter.init(10);
      updateCounter(n, 1);
      updateCounter(phi, -1);
      if (counter.zeroCnt != 10) {
        continue;
      }
      if (static_cast<uint64_t>(num) * phi >= static_cast<uint64_t>(n) * den) {
        num = n;
        den = phi;
        answers.push_back(n);
      }
    }
  }
  printf("answers[%lu]={", answers.size());
  bool first = true;
  for (auto answer : answers) {
    if (!first) {
      putchar(',');
    } else {
      first = false;
    }
    printf("%d", answer);
  }
  puts("}");
}
