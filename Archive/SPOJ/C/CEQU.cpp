#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <tuple>
#include <vector>

#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/gcd.h"

using namespace std;

int a, b, c;

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    io::readInt(a);
    io::readInt(b);
    io::readInt(c);
    io::writeCharArray("Case ");
    io::writeInt(taskIdx);
    io::writeCharArray(": ");
    io::writeCharArray(c % math::gcd(a, b) ? "No" : "Yes");
    io::writeChar('\n');
  }
  return 0;
}
