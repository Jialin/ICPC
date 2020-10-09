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
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/mod/log.h"

const int MAXN = 46341;

math::LogMod<> logMod(MAXN, 46341);
int a, b, mod;

int main() {
  while (true) {
    io::readInt(a);
    io::readInt(mod);
    io::readInt(b);
    if (!a && !mod && !b) {
      break;
    }
    int res;
    if (logMod.calc(a, b, mod, res)) {
      io::writeInt(res);
    } else {
      io::writeCharArray("No Solution");
    }
    io::writeChar('\n');
  }
  return 0;
}
