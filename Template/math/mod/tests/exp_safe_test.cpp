#include "gtest/gtest.h"

#include "math/mod/exp_safe.h"

namespace math {

TEST(ExpModSafeTest, normal) {
  EXPECT_EQ(expModSafe(2, 3, 5), 3);
  EXPECT_EQ(expModSafe(2, 2147483647, 13), 11);
  EXPECT_EQ(expModSafe(1463, 1397372724, 29478), 27031);
}

TEST(ExpModSafeTest, mod1) {
  EXPECT_EQ(expModSafe(1, 0, 1), 0);
  EXPECT_EQ(expModSafe(2, 3, 1), 0);
}

} // namespace math
