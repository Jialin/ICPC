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

const int MAXN = 100000 + 1;

int xs[MAXN];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  for (int i = 1; i <= n; ++i) {
    int x;
    io::readInt(x);
    xs[i] = x == 3 || x == 4 || x == 6;
  }
  for (int i = 2; i <= n; ++i) {
    xs[i] += xs[i - 1];
  }
  for (int i = 0; i < q; ++i) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    io::writeInt(l <= r ? xs[r] - xs[l - 1] : 0);
    io::writeChar('\n');
  }
}
