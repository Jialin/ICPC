#include "gtest/gtest.h"

#include "math/mod/log_coprime.h"

namespace math {

TEST(LogModCoprimeTest, basic) {
  LogModCoPrime<> logMod(100003);
  bool exist;

  exist = false;
  EXPECT_EQ(9, logMod.calc(5, 33, 58, exist));
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(4, logMod.calc(3, 13, 17, exist));
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(0, logMod.calc(3, 1, 17, exist));
  EXPECT_TRUE(exist);

  exist = true;
  logMod.calc(2, 3, 7, exist);
  EXPECT_FALSE(exist);
}

TEST(LogModCoprimeTest, resultLimit) {
  LogModCoPrime<> logMod(100003);
  bool exist;

  EXPECT_EQ(0, logMod.calc(5, 1, 100000007, exist));
  EXPECT_TRUE(exist);

  logMod.init(100003, true /* positiveResultOnly */);
  EXPECT_EQ(100000006, logMod.calc(5, 1, 100000007, exist));
  EXPECT_TRUE(exist);
}

} // namespace math
