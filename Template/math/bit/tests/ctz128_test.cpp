#include "gtest/gtest.h"

#include "math/bit/ctz128.h"

namespace math {

TEST(Ctz128, test) {
  EXPECT_EQ(ctz128(0), 128);
  EXPECT_EQ(ctz128(1), 0);
  EXPECT_EQ(ctz128(1024), 10);
  EXPECT_EQ(ctz128(__uint128_t(3) << 50), 50);
  EXPECT_EQ(ctz128(__uint128_t(3) << 70), 70);
  EXPECT_EQ(ctz128(__uint128_t(1024) << 70), 80);
}

} // namespace math
