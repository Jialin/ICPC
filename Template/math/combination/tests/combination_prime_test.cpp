#include "gtest/gtest.h"

#include "math/combination/combination_prime.h"

namespace math {

TEST(CombinationModPrimeTest, mod2) {
  CombinationModPrime<> comb(6, 2, 1);
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

TEST(CombinationModPrimeTest, mod3) {
  CombinationModPrime<> comb(6, 3, 1);
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

TEST(CombinationModPrimeTest, mod4) {
  CombinationModPrime<> comb(6, 2, 2);
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
  EXPECT_EQ(comb.calc(4, 1), 0);
  EXPECT_EQ(comb.calc(4, 2), 2);
  EXPECT_EQ(comb.calc(4, 3), 0);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 1);
  EXPECT_EQ(comb.calc(5, 2), 2);
  EXPECT_EQ(comb.calc(5, 3), 2);
  EXPECT_EQ(comb.calc(5, 4), 1);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModPrimeTest, largeMod) {
  CombinationModPrime<> comb(6, 100007, 1);
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

  comb.init(100000, 1000000007, 1);
  EXPECT_EQ(comb.calc(1231, 300), 296144006);
  EXPECT_EQ(comb.calc(99999, 44454), 750649176);

  CombinationModPrime<int64_t> comb64(100000, 2147483647, 1);
  EXPECT_EQ(comb64.calc(1231, 300), 1924759492);
  EXPECT_EQ(comb64.calc(99999, 44454), 255651975);
}

} // namespace math
