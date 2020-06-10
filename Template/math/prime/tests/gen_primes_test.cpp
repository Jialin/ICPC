#include "gtest/gtest.h"

#include "math/prime/gen_primes.h"

namespace math {

TEST(GenPrimes, test) {
  vector<int> primes;
  vector<int> smallestPrime;
  genPrimes(20, primes, smallestPrime);
  ASSERT_EQ(primes.size(), 8);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 3);
  EXPECT_EQ(primes[2], 5);
  EXPECT_EQ(primes[3], 7);
  EXPECT_EQ(primes[4], 11);
  EXPECT_EQ(primes[5], 13);
  EXPECT_EQ(primes[6], 17);
  EXPECT_EQ(primes[7], 19);
  ASSERT_EQ(smallestPrime.size(), 21);
  EXPECT_EQ(smallestPrime[0], -1);
  EXPECT_EQ(smallestPrime[1], -1);
  EXPECT_EQ(smallestPrime[2], 2);
  EXPECT_EQ(smallestPrime[3], 3);
  EXPECT_EQ(smallestPrime[4], 2);
  EXPECT_EQ(smallestPrime[5], 5);
  EXPECT_EQ(smallestPrime[6], 2);
  EXPECT_EQ(smallestPrime[7], 7);
  EXPECT_EQ(smallestPrime[8], 2);
  EXPECT_EQ(smallestPrime[9], 3);
  EXPECT_EQ(smallestPrime[10], 2);
  EXPECT_EQ(smallestPrime[11], 11);
  EXPECT_EQ(smallestPrime[12], 2);
  EXPECT_EQ(smallestPrime[13], 13);
  EXPECT_EQ(smallestPrime[14], 2);
  EXPECT_EQ(smallestPrime[15], 3);
  EXPECT_EQ(smallestPrime[16], 2);
  EXPECT_EQ(smallestPrime[17], 17);
  EXPECT_EQ(smallestPrime[18], 2);
  EXPECT_EQ(smallestPrime[19], 19);
  EXPECT_EQ(smallestPrime[20], 2);
}

} // namespace math
