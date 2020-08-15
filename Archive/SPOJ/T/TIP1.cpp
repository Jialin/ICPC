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

#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

const int CNT = 44;
const int ANSWERS[CNT] = {
    21,      63,      291,     2817,    2991,    4435,    20617,   45421,
    69271,   75841,   162619,  176569,  284029,  400399,  474883,  732031,
    778669,  783169,  1014109, 1288663, 1504051, 1514419, 1924891, 1956103,
    2006737, 2044501, 2094901, 2239261, 2710627, 2868469, 3582907, 3689251,
    4198273, 4696009, 5050429, 5380657, 5886817, 6018163, 6636841, 7026037,
    7357291, 7507321, 8316907, 8319823};

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    auto idx = upper_bound(ANSWERS, ANSWERS + CNT, n - 1) - ANSWERS;
    if (!idx) {
      io::writeCharArray("No solution.");
    } else {
      io::writeInt(ANSWERS[idx - 1]);
    }
    io::writeChar('\n');
  }
  return 0;
}

// #include "collections/unique_counter.h"
// #include "math/pow10.h"
// #include "math/prime/phi_all.h"

// const int MAXDIGIT = 7;
// const int BOUND = math::POW10[MAXDIGIT + 1];

// math::PhiAll phiAll(BOUND);
// collections::UniqueCounter counter(10, 10);
// vector<int> answers;

// inline void updateCounter(int n, int delta) {
//   for (; n > 0; n /= 10) {
//     counter.update(n % 10, delta);
//   }
// }

// int main() {
//   int num = 1, den = 0;
//   for (int digit = 2; digit <= MAXDIGIT; ++digit) {
//     for (int n = math::POW10[digit - 1]; n < math::POW10[digit]; ++n) {
//       int phi = phiAll.get(n);
//       if (phi < math::POW10[digit - 1]) {
//         continue;
//       }
//       counter.init(10);
//       updateCounter(n, 1);
//       updateCounter(phi, -1);
//       if (counter.zeroCnt != 10) {
//         continue;
//       }
//       if (static_cast<uint64_t>(num) * phi >= static_cast<uint64_t>(n) * den)
//       {
//         num = n;
//         den = phi;
//         answers.push_back(n);
//       }
//     }
//   }
//   printf("answers[%lu]={", answers.size());
//   bool first = true;
//   for (auto answer : answers) {
//     if (!first) {
//       putchar(',');
//     } else {
//       first = false;
//     }
//     printf("%d", answer);
//   }
//   puts("}");
// }
