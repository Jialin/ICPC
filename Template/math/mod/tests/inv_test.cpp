#include "gtest/gtest.h"

#include "math/mod/inv.h"

namespace math {

TEST(InvMod, test) {
  EXPECT_EQ(invMod(2, 3), 2);
  EXPECT_EQ(invMod(17, 101), 6);
  EXPECT_EQ(invMod(12345, 1000000007), 203483193);
}

} // namespace math
