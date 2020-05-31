#include "gtest/gtest.h"

#include "math/ext_gcd.h"

namespace math {

TEST(ExtGcd, test) {
  int x, y;

  EXPECT_EQ(extGcd(2, 1, x, y), 1);
  EXPECT_EQ(x, 0);
  EXPECT_EQ(y, 1);

  EXPECT_EQ(extGcd(17, 101, x, y), 1);
  EXPECT_EQ(x, 6);
  EXPECT_EQ(y, -1);

  EXPECT_EQ(extGcd(34, 202, x, y), 2);
  EXPECT_EQ(x, 6);
  EXPECT_EQ(y, -1);
}

} // namespace math
