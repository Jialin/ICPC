#include "gtest/gtest.h"

#include "math/gcd.h"

namespace math {

TEST(Gcd, test) {
  EXPECT_EQ(gcd(2, 1), 1);
  EXPECT_EQ(gcd(17, 101), 1);
  EXPECT_EQ(gcd(34, 202), 2);
  EXPECT_EQ(gcd(59528151, 4245384), 3711);
}

} // namespace math
