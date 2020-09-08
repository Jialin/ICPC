#include "gtest/gtest.h"

#include "math/mod/log_coprime.h"

namespace math {

TEST(LogModCoprimeTest, basic) {
  int res;

  EXPECT_TRUE(logModCoPrime(5, 33, 58, res));
  EXPECT_EQ(res, 9);

  EXPECT_TRUE(logModCoPrime(3, 13, 17, res));
  EXPECT_EQ(res, 4);

  EXPECT_TRUE(logModCoPrime(3, 1, 17, res));
  EXPECT_EQ(res, 0);

  // TODO(jialino): non coprime
  // EXPECT_EQ(logModCoPrime(2, 3, 4), -1);

  EXPECT_FALSE(logModCoPrime(2, 3, 7, res));
}

} // namespace math
