#include "gtest/gtest.h"

#include "math/gcd64.h"

namespace math {

TEST(Gcd64, testSmall) {
  EXPECT_EQ(gcd64(2, 1), 1);
  EXPECT_EQ(gcd64(17, 101), 1);
  EXPECT_EQ(gcd64(34, 202), 2);
  EXPECT_EQ(gcd64(59528151, 4245384), 3711);
  EXPECT_EQ(gcd64(59528151, 4245384), 3711);
}

TEST(Gcd64, testLarge) {
  EXPECT_EQ(gcd64(1000000000000037ULL, 1000000000000000ULL), 1);
  EXPECT_EQ(
      gcd64(1000000000000037ULL * 10001, 1000000000000037ULL * 10003),
      1000000000000037);
}

} // namespace math
