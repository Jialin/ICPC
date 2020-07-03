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
#include "math/prime/segmented_prime_iterator.h"

const int MAXTASK = 10;

int lower[MAXTASK], upper[MAXTASK];

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  int bound = 0;
  int maxGap = 0;
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readInt(lower[taskIdx]);
    io::readInt(upper[taskIdx]);
    ++upper[taskIdx];
    bound = max(bound, upper[taskIdx]);
    maxGap = max(maxGap, upper[taskIdx] - lower[taskIdx]);
  }
  math::SegmentedPrimeIterator<> spi(bound, maxGap);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    if (taskIdx) {
      io::writeChar('\n');
    }
    spi.iterate(lower[taskIdx], upper[taskIdx], [](int prime) {
      io::writeInt(prime);
      io::writeChar('\n');
    });
  }
  return 0;
}
