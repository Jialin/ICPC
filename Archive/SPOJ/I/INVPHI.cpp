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
#include "math/prime/phi_inv32.h"
#include "math/prime/prime_generator.h"

const int BOUND = 10000 + 1;

math::PrimeGenerator generator(BOUND, 1229);
math::PhiInv32 phiInv(generator.primes);

int main() {
  int res;
  auto processor = [&res](int v) { res = res < 0 ? v : min(res, v); };
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    res = -1;
    phiInv.calc(n, processor);
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
