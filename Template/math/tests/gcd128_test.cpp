#include "gtest/gtest.h"

#include "math/gcd128.h"

namespace math {

TEST(Gcd128, testSmall) {
  EXPECT_EQ(gcd128(2, 1), 1);
  EXPECT_EQ(gcd128(17, 101), 1);
  EXPECT_EQ(gcd128(34, 202), 2);
  EXPECT_EQ(gcd128(59528151, 4245384), 3711);
  EXPECT_EQ(gcd128(59528151, 4245384), 3711);
}

TEST(Gcd128, testLarge) {
  EXPECT_EQ(gcd128(1000000000000037ULL, 1000000000000000ULL), 1);
  EXPECT_EQ(
      gcd128(1000000000000037ULL * 10001, 1000000000000037ULL * 10003),
      1000000000000037);
  __uint128_t v = 100000000000000000ULL;
  v = v * 1000000000 + 67;
  __uint128_t u = v;
  v *= 101;
  u *= 707;
  EXPECT_EQ(gcd128(u, v), u / 7);
}

} // namespace math
