#include "gtest/gtest.h"

#include "math/bit/ctz.h"

namespace math {

TEST(CtzTest, bit32) {
  EXPECT_EQ(ctz(0), 32);
  EXPECT_EQ(ctz(0U), 32);
  EXPECT_EQ(ctz(1), 0);
  EXPECT_EQ(ctz(2), 1);
  EXPECT_EQ(ctz(256), 8);
}

TEST(CtzTest, bit64) {
  EXPECT_EQ(ctz(0LL), 64);
  EXPECT_EQ(ctz(0ULL), 64);
  EXPECT_EQ(ctz(1ULL), 0);
  EXPECT_EQ(ctz(2ULL), 1);
  EXPECT_EQ(ctz(1ULL << 50), 50);
}

} // namespace math
