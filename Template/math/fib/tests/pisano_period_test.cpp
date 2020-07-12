#include "gtest/gtest.h"

#include "math/fib/pisano_period.h"

namespace math {

TEST(PisanoPeriod, testSmall) {
  MinPrimeTagger mpt;
  PisanoPeriod pp(12, mpt);

  EXPECT_EQ(pp.calc(1), 1);
  EXPECT_EQ(pp.calc(2), 3);
  EXPECT_EQ(pp.calc(3), 8);
  EXPECT_EQ(pp.calc(4), 6);
  EXPECT_EQ(pp.calc(5), 20);
  EXPECT_EQ(pp.calc(11), 10);
}

TEST(PisanoPeriod, testLarge) {
  MinPrimeTagger mpt;
  PisanoPeriod pp(987655, mpt);

  EXPECT_EQ(pp.calc(123456), 15456);
  EXPECT_EQ(pp.calc(987654), 332808);
}

} // namespace math
