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

const int BOUND = 1000000 + 1;

math::MinPrimeTagger tagger(BOUND);
uint64_t vs[BOUND];

int main() {
  vs[1] = 1;
  for (int n = 2; n < BOUND; ++n) {
    int p, cnt, nxtN;
    tagger.process(n, p, cnt, nxtN);
    vs[n] = vs[nxtN] * (n / nxtN / p) * (p * cnt - cnt + p);
  }
  vs[1] -= 1;
  for (int n = 2; n < BOUND; ++n) {
    vs[n] += vs[n - 1] - n;
  }
  int n;
  while (true) {
    io::readInt(n);
    if (!n) {
      break;
    }
    io::writeInt(vs[n]);
    io::writeChar('\n');
  }
  return 0;
}
