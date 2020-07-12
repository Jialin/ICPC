#include "gtest/gtest.h"

#include "math/prime/prime_iterator.h"

namespace math {

TEST(PrimeIterator, test1E8Every100) {
  int bound = 100000000;
  PrimeIterator pi(bound);
  int cnt = 99;
  vector<uint32_t> primes;
  pi.iterate(bound, [&cnt, &primes](uint32_t p) {
    if (cnt == 99) {
      primes.push_back(p);
      cnt = 0;
    } else {
      ++cnt;
    }
    return true;
  });
  ASSERT_EQ(primes.size(), 57615);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 547);
  EXPECT_EQ(primes[2], 1229);
  EXPECT_EQ(primes[57612], 99995257);
  EXPECT_EQ(primes[57613], 99996931);
  EXPECT_EQ(primes[57614], 99998953);
}

TEST(PrimeIterator, test1E9Every500) {
  int bound = 1000000000;
  PrimeIterator pi(bound);
  int cnt = 499;
  vector<uint32_t> primes;
  pi.iterate(bound, [&cnt, &primes](uint32_t p) {
    if (cnt == 499) {
      primes.push_back(p);
      cnt = 0;
    } else {
      ++cnt;
    }
    return true;
  });
  ASSERT_EQ(primes.size(), 101696);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 3581);
  EXPECT_EQ(primes[2], 7927);
  EXPECT_EQ(primes[101693], 999978527);
  EXPECT_EQ(primes[101694], 999988747);
  EXPECT_EQ(primes[101695], 999999151);
}

} // namespace math
