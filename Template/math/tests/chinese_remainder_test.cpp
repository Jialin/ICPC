#include "gtest/gtest.h"

#include "math/chinese_remainder.h"

namespace math {

TEST(ChineseRemainderTest, coPrime) {
  int r, lcm;

  chineseRemainder(0, 1, 3, 4, r, lcm);
  EXPECT_EQ(r, 3);
  EXPECT_EQ(lcm, 4);

  chineseRemainder(0, 3, 3, 4, r, lcm);
  EXPECT_EQ(r, 3);
  EXPECT_EQ(lcm, 12);

  chineseRemainder(3, 12, 4, 5, r, lcm);
  EXPECT_EQ(r, 39);
  EXPECT_EQ(lcm, 60);
}

TEST(ChineseRemainderTest, nonCoPrime) {
  int r, lcm;

  chineseRemainder(1, 6, 1, 6, r, lcm);
  EXPECT_EQ(r, 1);
  EXPECT_EQ(lcm, 6);

  chineseRemainder(5, 21, 11, 39, r, lcm);
  EXPECT_EQ(r, 89);
  EXPECT_EQ(lcm, 273);
}

TEST(ChineseRemainderTest, large) {
  int64_t r, lcm;

  chineseRemainder<int64_t, __int128_t>(
      10001, 1000000007, 1222212, 1000000009, r, lcm);
  EXPECT_EQ(r, 499393902495767294);
  EXPECT_EQ(lcm, 1000000016000000063);
}

} // namespace math
