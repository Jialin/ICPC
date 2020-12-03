#include "gtest/gtest.h"

#include "math/fib/fib_utils.h"

namespace math {

TEST(FibUtils, testSmall) {
  FibUtils<> fibUtils(1000000007, 64);
  EXPECT_EQ(0, fibUtils.exp(0));
  EXPECT_EQ(1, fibUtils.exp(1));
  EXPECT_EQ(1, fibUtils.exp(2));
  EXPECT_EQ(2, fibUtils.exp(3));
  EXPECT_EQ(3, fibUtils.exp(4));
  EXPECT_EQ(5, fibUtils.exp(5));
  EXPECT_EQ(8, fibUtils.exp(6));
  EXPECT_EQ(13, fibUtils.exp(7));
}

TEST(FibUtils, testMod1) {
  FibUtils<> fibUtils(1, 64);
  EXPECT_EQ(0, fibUtils.exp(0));
  EXPECT_EQ(0, fibUtils.exp(1));
  EXPECT_EQ(0, fibUtils.exp(2));
}

TEST(FibUtils, testMod5) {
  FibUtils<> fibUtils(5, 64);
  EXPECT_EQ(0, fibUtils.exp(0));
  EXPECT_EQ(1, fibUtils.exp(1));
  EXPECT_EQ(1, fibUtils.exp(2));
  EXPECT_EQ(2, fibUtils.exp(3));
  EXPECT_EQ(3, fibUtils.exp(4));
  EXPECT_EQ(0, fibUtils.exp(5));
  EXPECT_EQ(3, fibUtils.exp(6));
  EXPECT_EQ(3, fibUtils.exp(7));
}

TEST(FibUtils, testBig) {
  FibUtils<> fibUtils(1000000007, 64);
  EXPECT_EQ(832040, fibUtils.exp(30));
  EXPECT_EQ(1346269, fibUtils.exp(31));
  EXPECT_EQ(701408733, fibUtils.exp(44));
  EXPECT_EQ(134903163, fibUtils.exp(45));
  EXPECT_EQ(778742000, fibUtils.exp(49));
  EXPECT_EQ(586268941, fibUtils.exp(50));
  EXPECT_EQ(365010934, fibUtils.exp(51));
  EXPECT_EQ(8745084, fibUtils.exp(60));
  EXPECT_EQ(730764433, fibUtils.exp(61));
  EXPECT_EQ(739509517, fibUtils.exp(62));
}

} // namespace math
