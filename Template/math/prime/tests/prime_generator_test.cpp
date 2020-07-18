#include "gtest/gtest.h"

#include "math/prime/prime_generator.h"

namespace math {

TEST(PrimeGeneratorTest, small) {
  PrimeGenerator pg(100);
  auto& primes = pg.primes;
  ASSERT_EQ(primes.size(), 25);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[1], 3);
  EXPECT_EQ(primes[2], 5);
  EXPECT_EQ(primes[3], 7);
  EXPECT_EQ(primes[4], 11);
  EXPECT_EQ(primes[5], 13);
  EXPECT_EQ(primes[6], 17);
  EXPECT_EQ(primes[7], 19);
  EXPECT_EQ(primes[8], 23);
  EXPECT_EQ(primes[9], 29);
  EXPECT_EQ(primes[10], 31);
  EXPECT_EQ(primes[11], 37);
  EXPECT_EQ(primes[12], 41);
  EXPECT_EQ(primes[13], 43);
  EXPECT_EQ(primes[14], 47);
  EXPECT_EQ(primes[15], 53);
  EXPECT_EQ(primes[16], 59);
  EXPECT_EQ(primes[17], 61);
  EXPECT_EQ(primes[18], 67);
  EXPECT_EQ(primes[19], 71);
  EXPECT_EQ(primes[20], 73);
  EXPECT_EQ(primes[21], 79);
  EXPECT_EQ(primes[22], 83);
  EXPECT_EQ(primes[23], 89);
  EXPECT_EQ(primes[24], 97);
}

TEST(PrimeGeneratorTest, till1E8Every100) {
  PrimeGenerator pg(100000000);
  auto& primes = pg.primes;
  ASSERT_EQ(primes.size(), 5761455);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[100], 547);
  EXPECT_EQ(primes[200], 1229);
  EXPECT_EQ(primes[5761200], 99995257);
  EXPECT_EQ(primes[5761300], 99996931);
  EXPECT_EQ(primes[5761400], 99998953);
}

TEST(PrimeGeneratorTest, till1E9Every500) {
  PrimeGenerator pg(1000000000);
  auto& primes = pg.primes;
  ASSERT_EQ(primes.size(), 50847534);
  EXPECT_EQ(primes[0], 2);
  EXPECT_EQ(primes[500], 3581);
  EXPECT_EQ(primes[1000], 7927);
  EXPECT_EQ(primes[50846500], 999978527);
  EXPECT_EQ(primes[50847000], 999988747);
  EXPECT_EQ(primes[50847500], 999999151);
}

} // namespace math
