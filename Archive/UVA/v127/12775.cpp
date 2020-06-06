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
#include "math/ext_gcd.h"
#include "math/gcd.h"

using namespace std;

inline long long calc(int A, int B, int C, int P) {
  int gcd = math::gcd(A, math::gcd(B, C));
  if (P % gcd) {
    return 0;
  }
  A /= gcd;
  B /= gcd;
  C /= gcd;
  P /= gcd;
  int x, y;
  gcd = math::extGcd(A, B, x, y);
  int dx = B / gcd, dy = A / gcd;
  while (x < 0 || y > 0) {
    x += dx;
    y -= dy;
  }
  long long res = 0;
  int remC = C % gcd, remP = P % gcd;
  for (; P >= 0; P -= C, remP -= remC) {
    if (remP < 0) {
      remP += gcd;
    }
    if (remP) {
      continue;
    }
    long long mul = P / gcd;
    long long newX = x * mul, newY = y * mul;
    mul = (-newY + dy - 1) / dy;
    newX -= mul * dx;
    newY += mul * dy;
    if (newX >= 0) {
      res += newX / dx + 1;
    }
  }
  return res;
}

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int A, B, C, P;
    io::readInt(A);
    io::readInt(B);
    io::readInt(C);
    io::readInt(P);
    printf("Case %d: %lld\n", taskIdx, calc(A, B, C, P));
  }
  return 0;
}
