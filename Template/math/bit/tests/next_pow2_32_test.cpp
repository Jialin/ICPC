#include "gtest/gtest.h"

#include "math/bit/next_pow2_32.h"

namespace math {

TEST(NextPow2_32, basic) {
  EXPECT_EQ(1, nextPow2_32(0));
  EXPECT_EQ(1, nextPow2_32(1));
  EXPECT_EQ(2, nextPow2_32(2));
  EXPECT_EQ(4, nextPow2_32(3));
  EXPECT_EQ(262144, nextPow2_32(183471));
  EXPECT_EQ(262144, nextPow2_32(262144));
}

} // namespace math
