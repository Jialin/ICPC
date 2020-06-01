#include "gtest/gtest.h"

#include "math/mod/mul.h"

namespace math {

TEST(MulMod, testSmall) {
  EXPECT_EQ(mulMod(2, 3, 7), 6);
  EXPECT_EQ(mulMod(2, 3, 5), 1);
}

TEST(MulMod, testLarge) {
  EXPECT_EQ(mulMod(999999991, 123123123, 1000000007), 30030046);
}

} // namespace math
