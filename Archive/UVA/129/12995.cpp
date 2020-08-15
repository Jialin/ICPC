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

const int BOUND = 1000000 + 1;

math::PhiAll phi(BOUND);
uint64_t vs[BOUND];

int main() {
  vs[1] = 0;
  for (int n = 2; n < BOUND; ++n) {
    vs[n] = vs[n - 1] + phi.get(n);
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
