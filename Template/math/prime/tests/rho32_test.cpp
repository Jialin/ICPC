#include "gtest/gtest.h"

#include "math/prime/rho32.h"

namespace math {

TEST(Rho32, testSmall) {
  EXPECT_EQ(rho32(4, 1, 2), 2);
  EXPECT_EQ(rho32(9, 1, 2), 3);
  EXPECT_EQ(rho32(121, 1, 4), 11);
}

TEST(Rho32, testLarge) {
  uint64_t v = rho32(2 * 1000000007ULL, 1, 2);
  EXPECT_TRUE(v == 2 || v == 1000000007);
}

} // namespace math
