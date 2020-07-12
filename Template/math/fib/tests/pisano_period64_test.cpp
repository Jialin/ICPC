#include "gtest/gtest.h"

#include "math/fib/pisano_period64.h"

namespace math {

TEST(PisanoPeriod64, testSmall) {
  MinPrimeTagger mpt;
  PisanoPeriod64 pp(6, mpt);

  EXPECT_EQ(pp.calc(1), 1);
  EXPECT_EQ(pp.calc(2), 3);
  EXPECT_EQ(pp.calc(3), 8);
  EXPECT_EQ(pp.calc(4), 6);
  EXPECT_EQ(pp.calc(5), 20);
  EXPECT_EQ(pp.calc(11), 10);
}

TEST(PisanoPeriod64, testLarge) {
  MinPrimeTagger mpt;
  PisanoPeriod64 pp(6, mpt);

  EXPECT_EQ(pp.calc(123456), 15456);
  EXPECT_EQ(pp.calc(987654), 332808);
  EXPECT_EQ(pp.calc(1000000007), 2000000016);
}

} // namespace math
