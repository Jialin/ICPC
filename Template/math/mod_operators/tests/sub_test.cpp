#include "gtest/gtest.h"

#include "math/mod_operators/sub.h"

namespace math {

TEST(SubMod, test) {
  EXPECT_EQ(subMod(2, 1, 4), 1);
  EXPECT_EQ(subMod(2, 2, 4), 0);
  EXPECT_EQ(subMod(2, 3, 4), 3);
  EXPECT_EQ(subMod(2, 4, 4), 2);
  EXPECT_EQ(subMod(2, 5, 4), 1);
  EXPECT_EQ(subMod(-1000, 2147483647, 1000000007), 852515374);
}

} // namespace math
