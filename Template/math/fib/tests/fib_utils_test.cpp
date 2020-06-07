#include "gtest/gtest.h"

#include "math/fib/fib_utils.h"

namespace math {

TEST(FibUtils, testSmall) {
  FibUtils<> fibUtils;
  EXPECT_EQ(fibUtils.exp(0), 0);
  EXPECT_EQ(fibUtils.exp(1), 1);
  EXPECT_EQ(fibUtils.exp(2), 1);
  EXPECT_EQ(fibUtils.exp(3), 2);
  EXPECT_EQ(fibUtils.exp(4), 3);
  EXPECT_EQ(fibUtils.exp(5), 5);
  EXPECT_EQ(fibUtils.exp(6), 8);
  EXPECT_EQ(fibUtils.exp(7), 13);
}

TEST(FibUtils, testMod1) {
  FibUtils<> fibUtils(1);
  EXPECT_EQ(fibUtils.exp(0), 0);
  EXPECT_EQ(fibUtils.exp(1), 0);
  EXPECT_EQ(fibUtils.exp(2), 0);
}

TEST(FibUtils, testBig) {
  FibUtils<> fibUtils;
  EXPECT_EQ(fibUtils.exp(30), 832040);
  EXPECT_EQ(fibUtils.exp(31), 1346269);
  EXPECT_EQ(fibUtils.exp(44), 701408733);
  EXPECT_EQ(fibUtils.exp(45), 134903163);
  EXPECT_EQ(fibUtils.exp(49), 778742000);
  EXPECT_EQ(fibUtils.exp(50), 586268941);
  EXPECT_EQ(fibUtils.exp(51), 365010934);
  EXPECT_EQ(fibUtils.exp(60), 8745084);
  EXPECT_EQ(fibUtils.exp(61), 730764433);
  EXPECT_EQ(fibUtils.exp(62), 739509517);
}

} // namespace math
