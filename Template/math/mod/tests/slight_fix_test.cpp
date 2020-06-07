#include "gtest/gtest.h"

#include "math/mod/slight_fix.h"

namespace math {

TEST(SlightFix, testTooSmall) {
  EXPECT_EQ(slightFixMod(-1, 3), 2);
  EXPECT_EQ(slightFixMod(-2, 3), 1);
  EXPECT_EQ(slightFixMod(-3, 3), 0);
  EXPECT_EQ(slightFixMod(-4, 3), -1);
  EXPECT_EQ(slightFixMod(-5, 3), -2);
}

TEST(SlightFix, testNoChange) {
  EXPECT_EQ(slightFixMod(0, 4), 0);
  EXPECT_EQ(slightFixMod(1, 4), 1);
  EXPECT_EQ(slightFixMod(2, 4), 2);
  EXPECT_EQ(slightFixMod(3, 4), 3);
}

TEST(SlightFix, testTooBig) {
  EXPECT_EQ(slightFixMod(3, 3), 0);
  EXPECT_EQ(slightFixMod(4, 3), 1);
  EXPECT_EQ(slightFixMod(5, 3), 2);
  EXPECT_EQ(slightFixMod(6, 3), 3);
  EXPECT_EQ(slightFixMod(7, 3), 4);
  EXPECT_EQ(slightFixMod(8, 3), 5);
}

} // namespace math
