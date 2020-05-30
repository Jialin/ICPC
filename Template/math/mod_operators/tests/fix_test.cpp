#include "gtest/gtest.h"

#include "math/mod_operators/fix.h"

namespace math {

TEST(Fix, testTooSmall) {
  EXPECT_EQ(fixMod(-1, 3), 2);
  EXPECT_EQ(fixMod(-2, 3), 1);
  EXPECT_EQ(fixMod(-3, 3), 0);
  EXPECT_EQ(fixMod(-4, 3), 2);
  EXPECT_EQ(fixMod(-5, 3), 1);
  EXPECT_EQ(fixMod(-6, 3), 0);
}

TEST(Fix, testNoChange) {
  EXPECT_EQ(fixMod(0, 4), 0);
  EXPECT_EQ(fixMod(1, 4), 1);
  EXPECT_EQ(fixMod(2, 4), 2);
  EXPECT_EQ(fixMod(3, 4), 3);
}

TEST(Fix, testTooBig) {
  EXPECT_EQ(fixMod(3, 3), 0);
  EXPECT_EQ(fixMod(4, 3), 1);
  EXPECT_EQ(fixMod(5, 3), 2);
  EXPECT_EQ(fixMod(6, 3), 0);
  EXPECT_EQ(fixMod(7, 3), 1);
  EXPECT_EQ(fixMod(8, 3), 2);
}

} // namespace math
