#include "gtest/gtest.h"

#include "math/mod/exp.h"

namespace math {

TEST(ExpModTest, normal) {
  EXPECT_EQ(3, expMod(2, 3, 5));
  EXPECT_EQ(11, expMod(2, 2147483647, 13));
  EXPECT_EQ(27031, expMod(1463, 1397372724, 29478));
}

TEST(ExpModTest, one) {
  EXPECT_EQ(0, expMod(2, 0, 1));
  EXPECT_EQ(0, expMod(2, 3, 1));
  EXPECT_EQ(0, expMod(2, 4, 1));
}

} // namespace math
