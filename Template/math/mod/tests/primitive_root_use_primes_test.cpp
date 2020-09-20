#include "gtest/gtest.h"

#include "math/mod/primitive_root_use_primes.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(primitiveRootUsePrimesTest, basic) {
  PrimeGenerator pg(7);
  PrimitiveRootUsePrimes<int> root;
  int res;
  EXPECT_TRUE(root.calc(1, pg.primes, res));
  EXPECT_EQ(res, 0);
  EXPECT_TRUE(root.calc(2, pg.primes, res));
  EXPECT_EQ(res, 1);
  EXPECT_TRUE(root.calc(3, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(4, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(5, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(6, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(7, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(9, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(10, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(11, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(13, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(14, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(17, pg.primes, res));
  EXPECT_EQ(res, 3);
  EXPECT_TRUE(root.calc(18, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(19, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(22, pg.primes, res));
  EXPECT_EQ(res, 7);
  EXPECT_TRUE(root.calc(23, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(25, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(26, pg.primes, res));
  EXPECT_EQ(res, 7);
  EXPECT_TRUE(root.calc(27, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(29, pg.primes, res));
  EXPECT_EQ(res, 2);
  EXPECT_TRUE(root.calc(31, pg.primes, res));
  EXPECT_EQ(res, 3);

  EXPECT_FALSE(root.calc(8, pg.primes, res));
  EXPECT_FALSE(root.calc(12, pg.primes, res));
  EXPECT_FALSE(root.calc(15, pg.primes, res));
  EXPECT_FALSE(root.calc(16, pg.primes, res));
  EXPECT_FALSE(root.calc(20, pg.primes, res));
  EXPECT_FALSE(root.calc(21, pg.primes, res));
  EXPECT_FALSE(root.calc(24, pg.primes, res));
  EXPECT_FALSE(root.calc(28, pg.primes, res));
  EXPECT_FALSE(root.calc(30, pg.primes, res));
  EXPECT_FALSE(root.calc(32, pg.primes, res));
  EXPECT_FALSE(root.calc(33, pg.primes, res));
  EXPECT_FALSE(root.calc(35, pg.primes, res));
  EXPECT_FALSE(root.calc(36, pg.primes, res));
}

TEST(primitiveRootUsePrimesTest, large) {
  PrimeGenerator pg(100000);
  PrimitiveRootUsePrimes<int> root;
  int res;
  EXPECT_TRUE(root.calc(1000000007, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(100000007, pg.primes, res));
  EXPECT_EQ(res, 5);
  EXPECT_TRUE(root.calc(998244353, pg.primes, res));
  EXPECT_EQ(res, 3);
}

} // namespace math
