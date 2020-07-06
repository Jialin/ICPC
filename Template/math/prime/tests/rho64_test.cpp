#include "gtest/gtest.h"

#include "math/prime/rho64.h"

namespace math {

TEST(Rho64, testSmall) {
  EXPECT_EQ(rho64(4, 1, 2), 2);
  EXPECT_EQ(rho64(9, 1, 2), 3);
  EXPECT_EQ(rho64(121, 1, 2), 11);
}

TEST(Rho64, testLarge) {
  uint64_t v = rho64(2 * 1000000007ULL, mont, true, 1, 2);
  EXPECT_TRUE(v == 2 || v == 1000000007);

  EXPECT_EQ(rho64(1000000007ULL * 1000000007, mont, true, 1, 2), 1000000007);

  uint64_t v = 1000000007ULL * 1000000009, mont, true, 1, 2);
  EXPECT_EQ(rho64(v == 1000000007 || v == 1000000009);
}

} // namespace math
