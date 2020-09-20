#include "gtest/gtest.h"

#include "math/mod/primitive_root_prime_use_primes.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(primitiveRootPrimeUsePrimesTest, basic) {
  PrimeGenerator pg(7);
  PrimitiveRootPrimeUsePrimes<int> root;
  int res;
  EXPECT_TRUE(root.calc(2, pg.primes, res));
  EXPECT_EQ(res, 1);
  EXPECT_TRUE(root.calc(3, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(5, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(7, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(11, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(13, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(17, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(19, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(23, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(29, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(31, pg.primes, res));
  EXPECT_EQ(res, 3);
}

TEST(primitiveRootPrimeUsePrimesTest, large) {
  PrimeGenerator pg(100000);
  PrimitiveRootPrimeUsePrimes<int> root;
  int res;
  EXPECT_TRUE(root.calc(1000000007, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(100000007, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(998244353, pg.primes, res));
  EXPECT_EQ(res, 3);
}

} // namespace math
