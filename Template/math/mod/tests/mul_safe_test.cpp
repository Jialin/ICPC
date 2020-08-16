#include "gtest/gtest.h"

#include "math/mod/mul_safe.h"

namespace math {

TEST(MulModSafe, small) {
  EXPECT_EQ(mulModSafe(2, 3, 7), 6);
  EXPECT_EQ(mulModSafe(2, 3, 5), 1);
}

TEST(MulModSafe, large) {
  EXPECT_EQ(mulModSafe(999999991, 123123123, 1000000007), 30030046);
}

} // namespace math
