#include "gtest/gtest.h"

#include "math/mod/primitive_root_use_primes.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(PrimitiveRootUsePrimesTest, exist) {
  PrimeGenerator pg(7);
  PrimitiveRootUsePrimes<int> root;
  bool exist;

  exist = false;
  EXPECT_EQ(root.calc(1, pg.primes, exist), 0);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(2, pg.primes, exist), 1);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(3, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(4, pg.primes, exist), 3);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(5, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(6, pg.primes, exist), 5);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(7, pg.primes, exist), 3);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(9, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(9, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(10, pg.primes, exist), 3);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(11, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(13, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(14, pg.primes, exist), 3);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(17, pg.primes, exist), 3);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(18, pg.primes, exist), 5);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(19, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(22, pg.primes, exist), 7);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(23, pg.primes, exist), 5);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(25, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(26, pg.primes, exist), 7);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(27, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(29, pg.primes, exist), 2);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(31, pg.primes, exist), 3);
  EXPECT_TRUE(exist);
}

TEST(PrimitiveRootUsePrimesTest, notExist) {
  PrimeGenerator pg(7);
  PrimitiveRootUsePrimes<int> root;
  bool exist;

  exist = true;
  root.calc(8, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(12, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(15, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(16, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(20, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(21, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(24, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(28, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(30, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(32, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(33, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(35, pg.primes, exist);
  EXPECT_FALSE(exist);

  exist = true;
  root.calc(36, pg.primes, exist);
  EXPECT_FALSE(exist);
}

TEST(PrimitiveRootUsePrimesTest, large) {
  PrimeGenerator pg(100000);
  PrimitiveRootUsePrimes<int> root;
  bool exist;

  exist = false;
  EXPECT_EQ(root.calc(100000007, pg.primes, exist), 5);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(998244353, pg.primes, exist), 3);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(root.calc(1000000007, pg.primes, exist), 5);
  EXPECT_TRUE(exist);
}

} // namespace math
