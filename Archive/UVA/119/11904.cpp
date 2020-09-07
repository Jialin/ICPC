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
#include "math/mod/combination.h"

const int MAXSUM = 1000000 + 1;
const int MOD = 1000000007;

math::CombinationMod combMod(MAXSUM, MOD);

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    int sum = 0, res = 1;
    for (int i = 0; i < n; ++i) {
      int t;
      io::readInt(t);
      sum += t;
      res = math::mulMod(res, combMod.calc(sum - 1, t - 1), MOD);
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeCharArray(": ");
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
