#include "gtest/gtest.h"

#include "math/mod/exp.h"

namespace math {

TEST(ExpMod, test) {
  EXPECT_EQ(expMod(2, 3, 5), 3);
  EXPECT_EQ(expMod(2, 2147483647, 13), 11);
  EXPECT_EQ(expMod(1463, 1397372724, 29478), 27031);
}

TEST(ExpMod, testMod1) {
  EXPECT_EQ(expMod(1, 0, 1), 0);
  EXPECT_EQ(expMod(2, 3, 1), 0);
}

} // namespace math
