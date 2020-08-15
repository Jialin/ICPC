#include "gtest/gtest.h"

#include "math/mod/mul_inline_safe.h"

namespace math {

TEST(MulModSafeTest, small) {
  int32_t res;

  res = 2;
  mulModInlineSafe(res, 3, 7);
  EXPECT_EQ(res, 6);

  res = 2;
  mulModInlineSafe(res, 3, 5);
  EXPECT_EQ(res, 1);
}

TEST(MulModSafeTest, large) {
  int32_t res;

  res = 999999991;
  mulModInlineSafe(res, 123123123, 1000000007);
  EXPECT_EQ(res, 30030046);
}

TEST(MulModSafeTest, overflow) {
  int32_t res;

  res = 999999991;
  mulModInlineSafe<int32_t, int32_t>(res, 123123123, 1000000007);
  EXPECT_EQ(res, 30030046);
}

} // namespace math
