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
#include "math/prime/factorize64.h"

int main() {
  uint64_t res;
  auto processor = [&res](uint64_t prime, int cnt) {
    uint64_t subRes = prime + 1;
    for (int i = 1; i < cnt; ++i) {
      subRes = subRes * prime + 1;
    }
    res *= subRes;
  };
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    uint64_t n;
    io::readInt(n);
    res = 1;
    math::factorize64(n, processor);
    io::writeInt(res - n);
    io::writeChar('\n');
  }
  return 0;
}
