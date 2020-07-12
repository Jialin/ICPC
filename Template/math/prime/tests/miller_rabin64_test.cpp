#include "gtest/gtest.h"

#include "math/prime/miller_rabin64.h"

namespace math {

TEST(MillerRabin64, testPrime) {
  EXPECT_TRUE(millerRabin64(2));
  EXPECT_TRUE(millerRabin64(3));
  EXPECT_TRUE(millerRabin64(1000000007));
}

TEST(MillerRabin64, testComposite) {
  EXPECT_FALSE(millerRabin64(0));
  EXPECT_FALSE(millerRabin64(1));
  EXPECT_FALSE(millerRabin64(4));
  EXPECT_FALSE(millerRabin64(561));
  EXPECT_FALSE(millerRabin64(3215031751));
}

TEST(MillerRabin64, testCarmichael) {
  EXPECT_FALSE(millerRabin64(6601));
  EXPECT_FALSE(millerRabin64(62745));
  EXPECT_FALSE(millerRabin64(63973));
  EXPECT_FALSE(millerRabin64(75361));
}

} // namespace math
