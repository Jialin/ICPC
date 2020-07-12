#include "gtest/gtest.h"

#include "math/gcd/ext_gcd.h"

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

TEST(ExtGcd, testNonPositive) {
  const long long kA = 152441433273129;
  const long long kB = 1238123131666861861;
  const long long kGcd = 1238123123;

  long long x, y;

  EXPECT_EQ(extGcd<long long>(kA, kB, x, y), kGcd);
  EXPECT_EQ(x, 71814365);
  EXPECT_EQ(y, -8842);
  EXPECT_EQ(kA * x + kB * y, kGcd);

  EXPECT_EQ(extGcd<long long>(-kA, kB, x, y), kGcd);
  EXPECT_EQ(x, -71814365);
  EXPECT_EQ(y, -8842);
  EXPECT_EQ(-kA * x + kB * y, kGcd);

  EXPECT_EQ(extGcd<long long>(kA, -kB, x, y), kGcd);
  EXPECT_EQ(x, 71814365);
  EXPECT_EQ(y, 8842);
  EXPECT_EQ(kA * x - kB * y, kGcd);

  EXPECT_EQ(extGcd<long long>(-kA, -kB, x, y), kGcd);
  EXPECT_EQ(x, -71814365);
  EXPECT_EQ(y, 8842);
  EXPECT_EQ(-kA * x - kB * y, kGcd);
}

} // namespace math
