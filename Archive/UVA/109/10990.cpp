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
#include "math/prime/phi_all.h"

const int BOUND = 2000000 + 1;

math::PhiAll phi(BOUND);
vector<int> phiDepth;

int main() {
  phiDepth.resize(BOUND);
  phiDepth[1] = 0;
  for (int i = 2; i < BOUND; ++i) {
    phiDepth[i] = phiDepth[phi.get(i)] + 1;
  }
  for (int i = 2; i < BOUND; ++i) {
    phiDepth[i] += phiDepth[i - 1];
  }
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, m;
    io::readInt(n);
    io::readInt(m);
    io::writeInt(phiDepth[m] - phiDepth[n - 1]);
    io::writeChar('\n');
  }
  return 0;
}
