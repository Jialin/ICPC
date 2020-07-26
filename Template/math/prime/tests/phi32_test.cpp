#include "gtest/gtest.h"

#include "math/prime/phi32.h"
#include "math/prime/prime_iterator.h"

namespace math {

TEST(Phi32, testSmall) {
  vector<int> primes{2, 3};
  EXPECT_EQ(phi32(0, primes), 0);
  EXPECT_EQ(phi32(1, primes), 1);
  EXPECT_EQ(phi32(2, primes), 1);
  EXPECT_EQ(phi32(3, primes), 2);
  EXPECT_EQ(phi32(4, primes), 2);
  EXPECT_EQ(phi32(5, primes), 4);
  EXPECT_EQ(phi32(7, primes), 6);
  EXPECT_EQ(phi32(12, primes), 4);
}

TEST(Phi32, testLarge) {
  vector<int> primes;
  PrimeIterator pi(10000);
  pi.iterate(1000, [&primes](int prime) {
    primes.push_back(prime);
    return true;
  });

  EXPECT_EQ(phi32(999999, primes), 466560);
  EXPECT_EQ(phi32(1000000, primes), 400000);
  EXPECT_EQ(phi32(123456, primes), 41088);
  EXPECT_EQ(phi32(7654321, primes), 7251444);
}

} // namespace math
