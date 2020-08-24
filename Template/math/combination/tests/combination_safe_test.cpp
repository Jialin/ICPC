#include "gtest/gtest.h"

#include "math/combination/combination_safe.h"

namespace math {

TEST(CombinationModSafeTest, mod2) {
  CombinationModSafe<> comb(6, 2);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 0);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 1);
  EXPECT_EQ(comb.calc(3, 2), 1);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 0);
  EXPECT_EQ(comb.calc(4, 2), 0);
  EXPECT_EQ(comb.calc(4, 3), 0);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 1);
  EXPECT_EQ(comb.calc(5, 2), 0);
  EXPECT_EQ(comb.calc(5, 3), 0);
  EXPECT_EQ(comb.calc(5, 4), 1);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModSafeTest, mod3) {
  CombinationModSafe<> comb(6, 3);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 2);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 0);
  EXPECT_EQ(comb.calc(3, 2), 0);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 1);
  EXPECT_EQ(comb.calc(4, 2), 0);
  EXPECT_EQ(comb.calc(4, 3), 1);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 2);
  EXPECT_EQ(comb.calc(5, 2), 1);
  EXPECT_EQ(comb.calc(5, 3), 1);
  EXPECT_EQ(comb.calc(5, 4), 2);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModSafeTest, largeMod) {
  CombinationModSafe<> comb(6, 100007);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 2);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 3);
  EXPECT_EQ(comb.calc(3, 2), 3);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 4);
  EXPECT_EQ(comb.calc(4, 2), 6);
  EXPECT_EQ(comb.calc(4, 3), 4);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 5);
  EXPECT_EQ(comb.calc(5, 2), 10);
  EXPECT_EQ(comb.calc(5, 3), 10);
  EXPECT_EQ(comb.calc(5, 4), 5);
  EXPECT_EQ(comb.calc(5, 5), 1);

  comb.init(100000, 1000000007);
  EXPECT_EQ(comb.calc(1231, 300), 296144006);
  EXPECT_EQ(comb.calc(99999, 44454), 750649176);
}

} // namespace math
