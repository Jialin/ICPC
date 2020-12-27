#include "gtest/gtest.h"

#define MOD_INT_ALL

#include "math/mod/mod_int.h"

namespace math {

TEST(ModInt, inv) {
  int res;
  res = ModInt<int, int, 3>(2).inv()._v;
  EXPECT_EQ(2, res);
  res = ModInt<int, int, 101>(17).inv()._v;
  EXPECT_EQ(6, res);
  res = ModInt<int, int64_t, 1000000007>(12345).inv()._v;
  EXPECT_EQ(203483193, res);
}

TEST(ModInt, exp) {
  int res;
  res = ModInt<int, int, 5>(2).exp(3)._v;
  EXPECT_EQ(3, res);
  res = ModInt<int, int, 13>(2).exp(2147483647)._v;
  EXPECT_EQ(11, res);
  res = ModInt<int, int, 29478>(1463).exp(139737272413132)._v;
  EXPECT_EQ(1633, res);
}

TEST(ModInt, expMod1) {
  int res;
  res = ModInt<int, int, 1>(2).exp(0)._v;
  EXPECT_EQ(0, res);
  res = ModInt<int, int, 1>(1938).exp(3)._v;
  EXPECT_EQ(0, res);
  res = ModInt<int, int, 1>(5).exp(4)._v;
  EXPECT_EQ(0, res);
}

} // namespace math
