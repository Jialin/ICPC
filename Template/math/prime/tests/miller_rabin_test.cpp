#include "gtest/gtest.h"

#include "math/prime/miller_rabin.h"

namespace math {

TEST(MillerRabin, testPrime) {
  EXPECT_TRUE(millerRabin(2));
  EXPECT_TRUE(millerRabin(3));
  EXPECT_TRUE(millerRabin(1000000007));
}

TEST(MillerRabin, testComposite) {
  EXPECT_FALSE(millerRabin(0));
  EXPECT_FALSE(millerRabin(1));
  EXPECT_FALSE(millerRabin(4));
  EXPECT_FALSE(millerRabin(561));
  EXPECT_FALSE(millerRabin(3215031751));
}

TEST(millerRabin, testCarmichael) {
  EXPECT_FALSE(millerRabin(6601));
  EXPECT_FALSE(millerRabin(62745));
  EXPECT_FALSE(millerRabin(63973));
  EXPECT_FALSE(millerRabin(75361));
}

} // namespace math
