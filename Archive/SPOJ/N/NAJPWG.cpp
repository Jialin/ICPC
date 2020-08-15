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
#include "math/prime/phi_all.h"

const int BOUND = 100000 + 1;

math::PhiAll phi(BOUND);
int ps[BOUND];

int main() {
  for (int n = 2; n < BOUND; ++n) {
    ps[n] = ps[n - 1] + n - 1 - phi.get(n);
  }
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    io::writeCharArray("Case ");
    io::writeInt(taskIdx);
    io::writeCharArray(": ");
    io::writeInt(ps[n] + n - 1);
    io::writeChar('\n');
  }
  return 0;
}
