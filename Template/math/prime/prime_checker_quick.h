
#pragma once

#include <cmath>
#include <vector>
using namespace std;

namespace math {

namespace {

const int PRIME_REMINDER_CNT = 8;
const int PRIME_LCM = 30;
const int PRIME_REMINDER[PRIME_REMINDER_CNT] = {1, 7, 11, 13, 17, 19, 23, 29};
const int PRIME_REMINDER_INV[PRIME_LCM] = {
    -1, 0,  -1, -1, -1, -1, -1, 1,  -1, -1, -1, 2,  -1, 3,  -1,
    -1, -1, 4,  -1, 5,  -1, -1, -1, 6,  -1, -1, -1, -1, -1, 7};
const int PRIME_MUL[PRIME_REMINDER_CNT][PRIME_REMINDER_CNT] = {
    {6, 4, 2, 4, 2, 4, 6, 2},
    {4, 6, 6, 4, 2, 4, 2, 2},
    {2, 2, 6, 6, 4, 2, 4, 4},
    {4, 4, 2, 6, 2, 4, 2, 6},
    {6, 2, 4, 2, 6, 2, 4, 4},
    {4, 4, 2, 4, 6, 6, 2, 2},
    {2, 2, 4, 2, 4, 6, 6, 4},
    {2, 6, 4, 2, 4, 2, 4, 6}};
const int PRIME_CARRY[PRIME_REMINDER_CNT][PRIME_REMINDER_CNT] = {
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 2, 2, 2, 1, 2, 2},
    {1, 1, 1, 3, 1, 2, 1, 3},
    {3, 1, 2, 1, 3, 1, 3, 3},
    {2, 2, 1, 2, 4, 4, 2, 2},
    {1, 1, 3, 1, 3, 5, 5, 4},
    {1, 6, 4, 2, 4, 2, 4, 6}};
const int PRIME_MODULE_IDX[PRIME_REMINDER_CNT][PRIME_REMINDER_CNT] = {
    {1, 2, 3, 4, 5, 6, 7, 0},
    {7, 5, 6, 2, 0, 4, 1, 3},
    {6, 7, 4, 5, 0, 2, 1, 3},
    {6, 7, 1, 0, 3, 2, 5, 4},
    {3, 2, 5, 4, 7, 6, 0, 1},
    {4, 6, 5, 7, 2, 3, 0, 1},
    {4, 6, 3, 7, 5, 1, 2, 0},
    {7, 0, 1, 2, 3, 4, 5, 6}};

} // namespace

class PrimeChecker {
public:
  inline PrimeChecker(int n = 30) {
    init(n);
  }

  inline void init(int n) {
    int size = n / PRIME_LCM + 1;
    isComposite_.assign(size, 0);
    isComposite_[0] = 1;
    int bound = static_cast<int>(sqrt(n) + 1);
    memcpy(mul_, PRIME_CARRY, sizeof(mul_));
    char* isCompositeEnd = isComposite_.data() + isComposite_.size();
    for (int i = 0, base = 0; base <= bound; ++i, base += PRIME_LCM) {
      for (int idx = 0; idx < PRIME_REMINDER_CNT; ++idx) {
        if (!(isComposite_[i] & (1 << idx))) {
          int v = base + PRIME_REMINDER[idx], vv = v * v;
          tag_(
              idx,
              isComposite_.data() + vv / PRIME_LCM,
              isCompositeEnd,
              PRIME_REMINDER_INV[vv % PRIME_LCM]);
        }
        mul_[idx][0] += PRIME_MUL[idx][0];
        mul_[idx][1] += PRIME_MUL[idx][1];
        mul_[idx][2] += PRIME_MUL[idx][2];
        mul_[idx][3] += PRIME_MUL[idx][3];
        mul_[idx][4] += PRIME_MUL[idx][4];
        mul_[idx][5] += PRIME_MUL[idx][5];
        mul_[idx][6] += PRIME_MUL[idx][6];
        mul_[idx][7] += PRIME_MUL[idx][7];
      }
    }
  }

  inline bool isPrime(int x) {
    if (x == 2 || x == 3 || x == 5) {
      return true;
    }
    int idx = PRIME_REMINDER_INV[x % PRIME_LCM];
    return idx >= 0 && !(isComposite_[x / PRIME_LCM] & (1 << idx));
  }

private:
  inline void
  tag_(int idx, char* isComposite, char* isCompositeEnd, int moduleIdx) {
    while (isComposite < isCompositeEnd) {
      *isComposite |= 1 << moduleIdx;
      isComposite += mul_[idx][moduleIdx];
      moduleIdx = PRIME_MODULE_IDX[idx][moduleIdx];
    }
  }

  vector<char> isComposite_;
  int mul_[PRIME_REMINDER_CNT][PRIME_REMINDER_CNT];
};

} // namespace math
