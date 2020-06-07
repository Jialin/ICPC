#include "gtest/gtest.h"

#include "math/fib/fib.h"

namespace math {

TEST(Fib, testSmall) {
  int a, b;

  tie(a, b) = fib<>(0, 1);
  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 0);

  tie(a, b) = fib<>(0, 1000000007);
  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 1);

  tie(a, b) = fib<>(1, 1000000007);
  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 1);

  tie(a, b) = fib<>(2, 1000000007);
  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 2);

  tie(a, b) = fib<>(2, 1000000007);
  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 2);

  tie(a, b) = fib<>(3, 1000000007);
  EXPECT_EQ(a, 2);
  EXPECT_EQ(b, 3);

  tie(a, b) = fib<>(4, 1000000007);
  EXPECT_EQ(a, 3);
  EXPECT_EQ(b, 5);
}

TEST(Fib, testBig) {
  int a, b;

  tie(a, b) = fib<>(30, 1000000007);
  EXPECT_EQ(a, 832040);
  EXPECT_EQ(b, 1346269);

  tie(a, b) = fib<>(44, 1000000007);
  EXPECT_EQ(a, 701408733);
  EXPECT_EQ(b, 134903163);

  tie(a, b) = fib<>(49, 1000000007);
  EXPECT_EQ(a, 778742000);
  EXPECT_EQ(b, 586268941);

  tie(a, b) = fib<>(50, 1000000007);
  EXPECT_EQ(a, 586268941);
  EXPECT_EQ(b, 365010934);

  tie(a, b) = fib<>(60, 1000000007);
  EXPECT_EQ(a, 8745084);
  EXPECT_EQ(b, 730764433);

  tie(a, b) = fib<>(61, 1000000007);
  EXPECT_EQ(a, 730764433);
  EXPECT_EQ(b, 739509517);
}

} // namespace math
