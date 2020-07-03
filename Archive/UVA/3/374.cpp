#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "math/mod_operators/exp.h"

using namespace std;

int main() {
  int b, p, m;
  while (scanf("%d%d%d", &b, &p, &m) != EOF) {
    printf("%d\n", math::expMod(b, p, m));
  }
  return 0;
}
