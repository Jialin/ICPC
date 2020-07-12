#include "gtest/gtest.h"

#include "math/gcd32.h"

namespace math {

TEST(Gcd32, test) {
  EXPECT_EQ(gcd32(2, 1), 1);
  EXPECT_EQ(gcd32(17, 101), 1);
  EXPECT_EQ(gcd32(34, 202), 2);
  EXPECT_EQ(gcd32(59528151, 4245384), 3711);
}

} // namespace math
