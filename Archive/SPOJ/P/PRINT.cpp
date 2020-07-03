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

const int MAXTASK = 150;

unsigned int lower[MAXTASK], upper[MAXTASK];

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  unsigned int bound = 0;
  int maxGap = 0;
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readInt(lower[taskIdx]);
    io::readInt(upper[taskIdx]);
    ++upper[taskIdx];
    bound = max(bound, upper[taskIdx]);
    maxGap = max(maxGap, static_cast<int>(upper[taskIdx] - lower[taskIdx]));
  }
  math::SegmentedPrimeIterator<unsigned int> spi(bound, maxGap);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    spi.iterate(lower[taskIdx], upper[taskIdx], [](unsigned int prime) {
      io::writeInt(prime);
      io::writeChar('\n');
    });
  }
  return 0;
}
