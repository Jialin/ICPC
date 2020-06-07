#include "gtest/gtest.h"

#include "math/fib/fib_partial_sum.h"

namespace math {

TEST(FibPartialSum, testSmall) {
  EXPECT_EQ(fibPartialSum(-100), 0);
  EXPECT_EQ(fibPartialSum(-1), 0);
  EXPECT_EQ(fibPartialSum(0), 0);
  EXPECT_EQ(fibPartialSum(1), 1);
  EXPECT_EQ(fibPartialSum(2), 2);
  EXPECT_EQ(fibPartialSum(3), 4);
  EXPECT_EQ(fibPartialSum(4), 7);
  EXPECT_EQ(fibPartialSum(5), 12);
  EXPECT_EQ(fibPartialSum(6), 20);
  EXPECT_EQ(fibPartialSum(7), 33);
}

TEST(FibPartialSum, testMod1) {
  EXPECT_EQ(fibPartialSum(0, 1), 0);
  EXPECT_EQ(fibPartialSum(1, 1), 0);
  EXPECT_EQ(fibPartialSum(2, 1), 0);
}

TEST(FibPartialSum, testBig) {
  EXPECT_EQ(fibPartialSum(28), 832039);
  EXPECT_EQ(fibPartialSum(29), 1346268);
  EXPECT_EQ(fibPartialSum(42), 701408732);
  EXPECT_EQ(fibPartialSum(43), 134903162);
  EXPECT_EQ(fibPartialSum(47), 778741999);
  EXPECT_EQ(fibPartialSum(48), 586268940);
  EXPECT_EQ(fibPartialSum(49), 365010933);
  EXPECT_EQ(fibPartialSum(58), 8745083);
  EXPECT_EQ(fibPartialSum(59), 730764432);
  EXPECT_EQ(fibPartialSum(60), 739509516);
}

} // namespace math
