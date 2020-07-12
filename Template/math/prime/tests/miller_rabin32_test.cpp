#include "gtest/gtest.h"

#include "math/prime/miller_rabin32.h"

namespace math {

TEST(MillerRabin32, testPrime) {
  EXPECT_TRUE(millerRabin32(2));
  EXPECT_TRUE(millerRabin32(3));
  EXPECT_TRUE(millerRabin32(1000000007));
}

TEST(MillerRabin32, testComposite) {
  EXPECT_FALSE(millerRabin32(0));
  EXPECT_FALSE(millerRabin32(1));
  EXPECT_FALSE(millerRabin32(4));
  EXPECT_FALSE(millerRabin32(561));
  EXPECT_FALSE(millerRabin32(3215031751));
}

TEST(MillerRabin32, testCarmichael) {
  EXPECT_FALSE(millerRabin32(6601));
  EXPECT_FALSE(millerRabin32(62745));
  EXPECT_FALSE(millerRabin32(63973));
  EXPECT_FALSE(millerRabin32(75361));
}

} // namespace math
