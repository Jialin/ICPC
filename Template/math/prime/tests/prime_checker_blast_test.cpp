#include "gtest/gtest.h"

#include "math/prime/prime_checker_blast.h"

namespace math {

TEST(PrimeChecker, test) {
  PrimeChecker pc(20);
  EXPECT_EQ(pc.isPrime(0), false);
  EXPECT_EQ(pc.isPrime(1), false);
  EXPECT_EQ(pc.isPrime(2), true);
  EXPECT_EQ(pc.isPrime(3), true);
  EXPECT_EQ(pc.isPrime(4), false);
  EXPECT_EQ(pc.isPrime(5), true);
  EXPECT_EQ(pc.isPrime(6), false);
  EXPECT_EQ(pc.isPrime(7), true);
  EXPECT_EQ(pc.isPrime(8), false);
  EXPECT_EQ(pc.isPrime(9), false);
  EXPECT_EQ(pc.isPrime(10), false);
  EXPECT_EQ(pc.isPrime(11), true);
  EXPECT_EQ(pc.isPrime(12), false);
  EXPECT_EQ(pc.isPrime(13), true);
  EXPECT_EQ(pc.isPrime(14), false);
  EXPECT_EQ(pc.isPrime(15), false);
  EXPECT_EQ(pc.isPrime(16), false);
  EXPECT_EQ(pc.isPrime(17), true);
  EXPECT_EQ(pc.isPrime(18), false);
  EXPECT_EQ(pc.isPrime(19), true);
  EXPECT_EQ(pc.isPrime(20), false);
}

} // namespace math
