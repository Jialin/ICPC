#include "gtest/gtest.h"

#include "math/gcd/gcd.h"

namespace math {

TEST(GcdTest, int32) {
  EXPECT_EQ(gcd(2, 1), 1);
  EXPECT_EQ(gcd(17, 101), 1);
  EXPECT_EQ(gcd(34, 202), 2);
  EXPECT_EQ(gcd(59528151, 4245384), 3711);
}

TEST(GcdTest, int64) {
  EXPECT_EQ(gcd(1000000000000037ULL, 1000000000000000ULL), 1);
  EXPECT_EQ(
      gcd(1000000000000037ULL * 10001, 1000000000000037ULL * 10003),
      1000000000000037LL);
}

TEST(GcdTest, int128) {
  EXPECT_EQ(gcd(1000000000000037ULL, 1000000000000000ULL), 1);
  EXPECT_EQ(
      gcd(1000000000000037ULL * 10001, 1000000000000037ULL * 10003),
      1000000000000037);
  __uint128_t v = __uint128_t(100000000000000000ULL) * 1000000000 + 67;
  __uint128_t u = v;
  v *= 101;
  u *= 707;
  EXPECT_EQ(gcd(u, v), u / 7);
}

} // namespace math
