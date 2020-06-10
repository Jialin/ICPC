#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/matrix/matrix_mod_exp_utils.h"
#include "math/mod/sub.h"

using namespace std;

constexpr int MOD = 1000000007;

math::MatrixModExpUtils<> expUtils;
math::Matrix<> res;

inline int calc(int n) {
  if (n <= 0) {
    return 0;
  }
  expUtils.exp(res, n);
  return res.at(1, 2);
}

int main() {
  math::Matrix<> base(3, 3);
  base.at(0, 1) = 1;
  base.at(1, 0) = 1;
  base.at(1, 1) = 1;
  base.at(1, 2) = 1;
  base.at(2, 2) = 1;
  expUtils.init(std::move(base), MOD, 32);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n, m;
    io::readInt(n);
    io::readInt(m);
    io::writeInt(n <= m ? math::subMod(calc(m), calc(n - 1), MOD) : 0);
    io::writeChar('\n');
  }
  return 0;
}
