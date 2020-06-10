#include "gtest/gtest.h"

#include "math/prime/prime_checker.h"

namespace math {

TEST(PrimeChecker, test) {
  PrimeChecker pc(20);
  EXPECT_EQ(pc.check(0), false);
  EXPECT_EQ(pc.check(1), false);
  EXPECT_EQ(pc.check(2), true);
  EXPECT_EQ(pc.check(3), true);
  EXPECT_EQ(pc.check(4), false);
  EXPECT_EQ(pc.check(5), true);
  EXPECT_EQ(pc.check(6), false);
  EXPECT_EQ(pc.check(7), true);
  EXPECT_EQ(pc.check(8), false);
  EXPECT_EQ(pc.check(9), false);
  EXPECT_EQ(pc.check(10), false);
  EXPECT_EQ(pc.check(11), true);
  EXPECT_EQ(pc.check(12), false);
  EXPECT_EQ(pc.check(13), true);
  EXPECT_EQ(pc.check(14), false);
  EXPECT_EQ(pc.check(15), false);
  EXPECT_EQ(pc.check(16), false);
  EXPECT_EQ(pc.check(17), true);
  EXPECT_EQ(pc.check(18), false);
  EXPECT_EQ(pc.check(19), true);
  EXPECT_EQ(pc.check(20), false);
}

} // namespace math
