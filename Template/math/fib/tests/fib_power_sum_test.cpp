#include "gtest/gtest.h"

#include "math/fib/fib_power_sum.h"

namespace math {

TEST(FibPowerSumTest, small) {
  FibPowerSum sum(1000000007, 5);
  EXPECT_EQ(sum.calc(0, 1), 0);
  EXPECT_EQ(sum.calc(1, 1), 1);
  EXPECT_EQ(sum.calc(2, 1), 2);
  EXPECT_EQ(sum.calc(3, 1), 4);
  EXPECT_EQ(sum.calc(4, 1), 7);
  EXPECT_EQ(sum.calc(0, 2), 0);
  EXPECT_EQ(sum.calc(1, 2), 1);
  EXPECT_EQ(sum.calc(2, 2), 2);
  EXPECT_EQ(sum.calc(3, 2), 6);
  EXPECT_EQ(sum.calc(4, 2), 15);
  EXPECT_EQ(sum.calc(0, 3), 0);
  EXPECT_EQ(sum.calc(1, 3), 1);
  EXPECT_EQ(sum.calc(2, 3), 2);
  EXPECT_EQ(sum.calc(3, 3), 10);
  EXPECT_EQ(sum.calc(4, 3), 37);
  EXPECT_EQ(sum.calc(0, 4), 0);
  EXPECT_EQ(sum.calc(1, 4), 1);
  EXPECT_EQ(sum.calc(2, 4), 2);
  EXPECT_EQ(sum.calc(3, 4), 18);
  EXPECT_EQ(sum.calc(4, 4), 99);
}

TEST(FibPowerSumTest, large) {
  FibPowerSum sum(1000000007, 200);
  EXPECT_EQ(sum.calc(100, 4), 47618639);
  EXPECT_EQ(sum.calc(1000, 4), 776749265);
  EXPECT_EQ(sum.calc(10000, 4), 727759042);
  EXPECT_EQ(sum.calc(100, 199), 287138516);
  EXPECT_EQ(sum.calc(1000, 199), 830126095);
  EXPECT_EQ(sum.calc(10000, 199), 910048127);
  EXPECT_EQ(sum.calc(10000000000000ULL, 1), 236227569);
  EXPECT_EQ(sum.calc(10000000000000ULL, 2), 588860823);
  EXPECT_EQ(sum.calc(10000000000000ULL, 199), 837039937);
}

} // namespace math
