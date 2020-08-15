#include "gtest/gtest.h"

#include "math/mod/exp.h"

namespace math {

TEST(ExpModTest, normal) {
  EXPECT_EQ(expMod(2, 3, 5), 3);
  EXPECT_EQ(expMod(2, 2147483647, 13), 11);
  EXPECT_EQ(expMod(1463, 1397372724, 29478), 27031);
}

} // namespace math
