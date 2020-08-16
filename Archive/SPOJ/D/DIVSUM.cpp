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
#include "io/write_int.h"
#include "math/prime/min_prime_tagger.h"

const int MAXN = 500000 + 1;

math::MinPrimeTagger tagger(MAXN);

int sums[MAXN], answers[MAXN];

int main() {
  sums[1] = 1;
  answers[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    int prime, primeCnt, nxtN;
    tagger.process(i, prime, primeCnt, nxtN);
    if (primeCnt == 1) {
      sums[i] = prime + 1;
    } else {
      sums[i] = sums[i / prime] * prime + 1;
    }
    answers[i] = answers[nxtN] * sums[i];
  }
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    io::writeInt(answers[n] - n);
    io::writeChar('\n');
  }
  return 0;
}
