#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "io/read_int.h"
#include "math/ext_gcd.h"

using namespace std;

int main() {
  int a, b;
  while (io::readInt(a) && io::readInt(b)) {
    int x, y;
    int gcd = math::extGcd(a, b, x, y);
    printf("%d %d %d\n", x, y, gcd);
  }
  return 0;
}
