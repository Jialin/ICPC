#include "gtest/gtest.h"

#include "math/mod/mul_inline.h"

namespace math {

TEST(MulModTest, small) {
  int32_t res;

  res = 2;
  mulModInline(res, 3, 7);
  EXPECT_EQ(res, 6);

  res = 2;
  mulModInline(res, 3, 5);
  EXPECT_EQ(res, 1);
}

TEST(MulModTest, large) {
  int32_t res;

  res = 999999991;
  mulModInline(res, 123123123, 1000000007);
  EXPECT_EQ(res, 30030046);
}

} // namespace math
