#include "gtest/gtest.h"

#include "math/mod/combination.h"

namespace math {

TEST(CombinationModTest, simple) {
  CombinationMod combMod(6, 100007);
  EXPECT_EQ(combMod.calc(0, 0), 1);
  EXPECT_EQ(combMod.calc(1, 1), 1);
  EXPECT_EQ(combMod.calc(1, 2), 0);
  EXPECT_EQ(combMod.calc(2, 0), 1);
  EXPECT_EQ(combMod.calc(2, 1), 2);
  EXPECT_EQ(combMod.calc(2, 2), 1);
  EXPECT_EQ(combMod.calc(3, 0), 1);
  EXPECT_EQ(combMod.calc(3, 1), 3);
  EXPECT_EQ(combMod.calc(3, 2), 3);
  EXPECT_EQ(combMod.calc(3, 3), 1);
  EXPECT_EQ(combMod.calc(4, 0), 1);
  EXPECT_EQ(combMod.calc(4, 1), 4);
  EXPECT_EQ(combMod.calc(4, 2), 6);
  EXPECT_EQ(combMod.calc(4, 3), 4);
  EXPECT_EQ(combMod.calc(4, 4), 1);
  EXPECT_EQ(combMod.calc(5, 0), 1);
  EXPECT_EQ(combMod.calc(5, 1), 5);
  EXPECT_EQ(combMod.calc(5, 2), 10);
  EXPECT_EQ(combMod.calc(5, 3), 10);
  EXPECT_EQ(combMod.calc(5, 4), 5);
  EXPECT_EQ(combMod.calc(5, 5), 1);
}

TEST(CombinationModTest, large) {
  CombinationMod combMod(100000, 1000000007);
  EXPECT_EQ(combMod.calc(1231, 300), 296144006);
  EXPECT_EQ(combMod.calc(99999, 44454), 750649176);
}

} // namespace math
