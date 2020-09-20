#include "gtest/gtest.h"

#include "math/mod/primitive_root_prime_use_primes.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(PrimitiveRootPrimeUsePrimesTest, basic) {
  PrimeGenerator pg(7);
  PrimitiveRootPrimeUsePrimes<int> root;
  EXPECT_EQ(root.calc(2, pg.primes), 1);
  EXPECT_EQ(root.calc(3, pg.primes), 2);
  EXPECT_EQ(root.calc(5, pg.primes), 2);
  EXPECT_EQ(root.calc(7, pg.primes), 3);
  EXPECT_EQ(root.calc(11, pg.primes), 2);
  EXPECT_EQ(root.calc(13, pg.primes), 2);
  EXPECT_EQ(root.calc(17, pg.primes), 3);
  EXPECT_EQ(root.calc(19, pg.primes), 2);
  EXPECT_EQ(root.calc(23, pg.primes), 5);
  EXPECT_EQ(root.calc(29, pg.primes), 2);
  EXPECT_EQ(root.calc(31, pg.primes), 3);
}

TEST(PrimitiveRootPrimeUsePrimesTest, large) {
  PrimeGenerator pg(100000);
  PrimitiveRootPrimeUsePrimes<int> root;
  EXPECT_EQ(root.calc(100000007, pg.primes), 5);
  EXPECT_EQ(root.calc(998244353, pg.primes), 3);
  EXPECT_EQ(root.calc(1000000007, pg.primes), 5);
}

} // namespace math
