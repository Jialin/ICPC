#pragma once

#include <vector>

#include "math/mod/exp.h"
#include "math/mod/fix.h"

using namespace std;

namespace math {

namespace {

// Checks whether a^n<b, if not res=a^n
template<typename T, typename EXP>
inline bool exceed(T base, EXP exp, T bound, T& res) {
  res = 1;
  T bound2 = bound / base;
  for (; exp && res < bound2; --exp, res *= base) {}
  return exp;
}

template<typename T>
inline T powerTowerDfs_(
    int depth, int size, const vector<T>& bases, const vector<T>& phis) {
  if (depth >= size) {
    return 1;
  }
  if (bases[depth] <= 1) {
    return bases[depth];
  }
  if (phis[depth] == 1) {
    return 1;
  }
  T subRes = powerTowerDfs_(depth + 1, size, bases, phis), res;
  if (!exceed(bases[depth], subRes, phis[depth], res)) {
    return res;
  }
  return expMod(fixMod(bases[depth], phis[depth]), subRes, phis[depth]) +
         phis[depth];
}

} // namespace

template<typename T>
inline T powerTower(const vector<T>& bases, const vector<T>& phis) {
  return fixMod<T>(
      powerTowerDfs_<T>(
          0, static_cast<int>(min(bases.size(), phis.size())), bases, phis),
      phis[0]);
}

} // namespace math
