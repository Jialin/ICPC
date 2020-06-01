#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "io/read_int.h"
#include "math/mod_operators/exp_quick.h"

using namespace std;

const int MOD = 1000000007;

vector<int> powList;
long long n;
long long cnt3ll;
int rem;
int mul;
int cnt3;
int res;

int main() {
  powList.reserve(32);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readInt(n);
    cnt3ll = n / 3;
    rem = n % 3;
    mul = 1;
    if (rem == 1) {
      if (cnt3ll > 0) {
        --cnt3ll;
        mul = 4;
      }
    } else if (rem == 2) {
      mul = 2;
    }
    if (cnt3ll >= MOD) {
      cnt3 = cnt3ll % (MOD - 1);
    } else {
      cnt3 = static_cast<int>(cnt3ll);
    }
    res = math::expModQuick(powList, 3, cnt3, MOD);
    if (mul != 1) {
      math::mulModInline(res, mul, MOD);
    }
    printf("%d\n", res);
  }
  return 0;
}
