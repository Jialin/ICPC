#include "gtest/gtest.h"

#include "math/prime/phi_use_primes.h"
#include "math/prime/prime_iterator.h"

namespace math {

TEST(PhiUsePrimesTest, small) {
  vector<int> primes{2, 3};
  EXPECT_EQ(phiUsePrimes(0, primes), 0);
  EXPECT_EQ(phiUsePrimes(1, primes), 1);
  EXPECT_EQ(phiUsePrimes(2, primes), 1);
  EXPECT_EQ(phiUsePrimes(3, primes), 2);
  EXPECT_EQ(phiUsePrimes(4, primes), 2);
  EXPECT_EQ(phiUsePrimes(5, primes), 4);
  EXPECT_EQ(phiUsePrimes(7, primes), 6);
  EXPECT_EQ(phiUsePrimes(12, primes), 4);
}

TEST(PhiUsePrimesTest, large) {
  vector<int> primes;
  PrimeIterator pi(10000);
  pi.iterate(3000, [&primes](int prime) {
    primes.push_back(prime);
    return true;
  });

  EXPECT_EQ(phiUsePrimes(999999, primes), 466560);
  EXPECT_EQ(phiUsePrimes(1000000, primes), 400000);
  EXPECT_EQ(phiUsePrimes(123456, primes), 41088);
  EXPECT_EQ(phiUsePrimes(7654321, primes), 7251444);
}

} // namespace math
