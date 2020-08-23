#include "gtest/gtest.h"

#include "math/fib/fib_sum.h"

namespace math {

TEST(FibSumTest, small) {
  EXPECT_EQ(fibSum(-100, 1000000007), 0);
  EXPECT_EQ(fibSum(-1, 1000000007), 0);
  EXPECT_EQ(fibSum(0, 1000000007), 0);
  EXPECT_EQ(fibSum(1, 1000000007), 1);
  EXPECT_EQ(fibSum(2, 1000000007), 2);
  EXPECT_EQ(fibSum(3, 1000000007), 4);
  EXPECT_EQ(fibSum(4, 1000000007), 7);
  EXPECT_EQ(fibSum(5, 1000000007), 12);
  EXPECT_EQ(fibSum(6, 1000000007), 20);
  EXPECT_EQ(fibSum(7, 1000000007), 33);
}

TEST(FibSumTest, mod1) {
  EXPECT_EQ(fibSum(0, 1), 0);
  EXPECT_EQ(fibSum(1, 1), 0);
  EXPECT_EQ(fibSum(2, 1), 0);
}

TEST(FibSumTest, large) {
  EXPECT_EQ(fibSum(28, 1000000007), 832039);
  EXPECT_EQ(fibSum(29, 1000000007), 1346268);
  EXPECT_EQ(fibSum(42, 1000000007), 701408732);
  EXPECT_EQ(fibSum(43, 1000000007), 134903162);
  EXPECT_EQ(fibSum(47, 1000000007), 778741999);
  EXPECT_EQ(fibSum(48, 1000000007), 586268940);
  EXPECT_EQ(fibSum(49, 1000000007), 365010933);
  EXPECT_EQ(fibSum(58, 1000000007), 8745083);
  EXPECT_EQ(fibSum(59, 1000000007), 730764432);
  EXPECT_EQ(fibSum(60, 1000000007), 739509516);
}

} // namespace math
