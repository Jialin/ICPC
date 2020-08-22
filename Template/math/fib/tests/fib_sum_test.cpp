#include "gtest/gtest.h"

#include "math/fib/fib_sum.h"

namespace math {

TEST(FibPartialSum, testSmall) {
  EXPECT_EQ(fibPartialSum(-100, 1000000007), 0);
  EXPECT_EQ(fibPartialSum(-1, 1000000007), 0);
  EXPECT_EQ(fibPartialSum(0, 1000000007), 0);
  EXPECT_EQ(fibPartialSum(1, 1000000007), 1);
  EXPECT_EQ(fibPartialSum(2, 1000000007), 2);
  EXPECT_EQ(fibPartialSum(3, 1000000007), 4);
  EXPECT_EQ(fibPartialSum(4, 1000000007), 7);
  EXPECT_EQ(fibPartialSum(5, 1000000007), 12);
  EXPECT_EQ(fibPartialSum(6, 1000000007), 20);
  EXPECT_EQ(fibPartialSum(7, 1000000007), 33);
}

TEST(FibPartialSum, testMod1) {
  EXPECT_EQ(fibPartialSum(0, 1), 0);
  EXPECT_EQ(fibPartialSum(1, 1), 0);
  EXPECT_EQ(fibPartialSum(2, 1), 0);
}

TEST(FibPartialSum, testBig) {
  EXPECT_EQ(fibPartialSum(28, 1000000007), 832039);
  EXPECT_EQ(fibPartialSum(29, 1000000007), 1346268);
  EXPECT_EQ(fibPartialSum(42, 1000000007), 701408732);
  EXPECT_EQ(fibPartialSum(43, 1000000007), 134903162);
  EXPECT_EQ(fibPartialSum(47, 1000000007), 778741999);
  EXPECT_EQ(fibPartialSum(48, 1000000007), 586268940);
  EXPECT_EQ(fibPartialSum(49, 1000000007), 365010933);
  EXPECT_EQ(fibPartialSum(58, 1000000007), 8745083);
  EXPECT_EQ(fibPartialSum(59, 1000000007), 730764432);
  EXPECT_EQ(fibPartialSum(60, 1000000007), 739509516);
}

} // namespace math
