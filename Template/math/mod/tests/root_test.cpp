#include "gtest/gtest.h"

#include "math/mod/primitive_root_use_primes.h"
#include "math/mod/root.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(RootModTest, exist) {
  PrimeGenerator pg(100000);
  PrimitiveRootUsePrimes<int> primitiveRoot;
  LogModCoPrime<int> logMod(100003);
  bool exist;
  int pr;

  exist = false;
  pr = primitiveRoot.calc(58, pg.primes, exist);
  EXPECT_EQ(pr, 3);
  EXPECT_TRUE(exist);
  exist = false;
  EXPECT_EQ(rootMod<>(9, 33, 58, pr, logMod, exist), 5);
  EXPECT_TRUE(exist);

  exist = false;
  pr = primitiveRoot.calc(17, pg.primes, exist);
  EXPECT_EQ(pr, 3);
  EXPECT_TRUE(exist);
  exist = false;
  EXPECT_EQ(rootMod<>(4, 13, 17, pr, logMod, exist), 3);
  EXPECT_TRUE(exist);
}

TEST(RootModTest, notExist) {
  // TODO
}

} // namespace math
