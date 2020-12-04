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

#include "debug/debug.h"
#include "io/write_int.h"
#include "math/gray_code.h"

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < 1 << n; ++i) {
    int64_t v = math::grayCode(i);
    for (int j = 0; j < 1 << m; ++j) {
      if (j > 0) {
        io::writeChar(' ');
      }
      io::writeInt((v << m) | math::grayCode(j));
    }
    io::writeChar('\n');
  }
}