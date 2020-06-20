#include "gtest/gtest.h"

#include "math/prime/prime_gen.h"

namespace math {

TEST(PrimeGenerator, test) {
  PrimeGenerator pg(20);
  const auto& primes = pg.primes;
  ASSERT_EQ(primes.size(), 8);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 3);
  EXPECT_EQ(primes[2], 5);
  EXPECT_EQ(primes[3], 7);
  EXPECT_EQ(primes[4], 11);
  EXPECT_EQ(primes[5], 13);
  EXPECT_EQ(primes[6], 17);
  EXPECT_EQ(primes[7], 19);
}

} // namespace math
