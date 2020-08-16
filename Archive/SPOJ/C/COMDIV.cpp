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
#include "math/gcd/gcd32.h"
#include "math/prime/min_prime_tagger.h"

const int MAXN = 1000000 + 1;

math::MinPrimeTagger tagger(MAXN);
int answers[MAXN];

int main() {
  answers[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    int prime, primeCnt, nxtN;
    tagger.process(i, prime, primeCnt, nxtN);
    answers[i] = answers[nxtN] * (primeCnt + 1);
  }
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int a, b;
    io::readInt(a);
    io::readInt(b);
    io::writeInt(answers[math::gcd32(a, b)]);
    io::writeChar('\n');
  }
  return 0;
}
