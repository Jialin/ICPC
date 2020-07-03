#include "gtest/gtest.h"

#include "math/prime/segmented_prime_iterator.h"

namespace math {

TEST(SegmentedPrimeIterator, test1E8Every100) {
  int bound = 100000000;
  SegmentedPrimeIterator<> spi(bound);
  int cnt;

  vector<int> primes;
  cnt = 99;
  spi.iterate(0, 1230, [&cnt, &primes](int p) {
    if (cnt == 99) {
      primes.push_back(p);
      cnt = 0;
    } else {
      ++cnt;
    }
  });
  ASSERT_EQ(primes.size(), 3);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 547);
  EXPECT_EQ(primes[2], 1229);

  primes.clear();
  cnt = 99;
  spi.iterate(99995256, 100000000, [&cnt, &primes](int p) {
    if (cnt == 99) {
      primes.push_back(p);
      cnt = 0;
    } else {
      ++cnt;
    }
  });
  ASSERT_EQ(primes.size(), 3);
  EXPECT_EQ(primes[0], 99995257);
  EXPECT_EQ(primes[1], 99996931);
  EXPECT_EQ(primes[2], 99998953);
}

TEST(PrimeIterator, test1E9Every500) {
  int bound = 1000000000;
  SegmentedPrimeIterator<> spi(bound);
  int cnt;

  vector<int> primes;
  cnt = 499;
  spi.iterate(0, 8000, [&cnt, &primes](int p) {
    if (cnt == 499) {
      primes.push_back(p);
      cnt = 0;
    } else {
      ++cnt;
    }
  });
  ASSERT_EQ(primes.size(), 3);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 3581);
  EXPECT_EQ(primes[2], 7927);

  primes.clear();
  cnt = 499;
  spi.iterate(999978524, 1000000000, [&cnt, &primes](int p) {
    if (cnt == 499) {
      primes.push_back(p);
      cnt = 0;
    } else {
      ++cnt;
    }
  });
  ASSERT_EQ(primes.size(), 3);
  EXPECT_EQ(primes[0], 999978527);
  EXPECT_EQ(primes[1], 999988747);
  EXPECT_EQ(primes[2], 999999151);
}

} // namespace math
