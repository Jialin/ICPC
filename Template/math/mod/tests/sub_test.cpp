#include "gtest/gtest.h"

#include "math/mod/sub.h"

namespace math {

TEST(SubMod, test) {
  EXPECT_EQ(1, subMod(2, 1, 4));
  EXPECT_EQ(0, subMod(2, 2, 4));
  EXPECT_EQ(3, subMod(2, 3, 4));
  EXPECT_EQ(2, subMod(2, 4, 4));
  EXPECT_EQ(1, subMod(2, 5, 4));
}

TEST(SubMod, testUnsigned) {
  EXPECT_EQ(subMod<uint64_t>(5, 2, 7), 3);
  EXPECT_EQ(subMod<uint64_t>(2, 5, 7), 4);
}

} // namespace math
