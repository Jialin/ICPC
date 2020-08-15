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

const int BOUND = 5000000 + 1;

math::PhiAll phi(BOUND);
uint64_t vs[BOUND];

int main() {
  for (int n = 1; n < BOUND; ++n) {
    uint64_t subRes = phi.get(n);
    vs[n] = vs[n - 1] + subRes * subRes;
  }
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeCharArray(": ");
    io::writeInt(vs[r] - vs[l - 1]);
    io::writeChar('\n');
  }
  return 0;
}
