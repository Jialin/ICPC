#include "gtest/gtest.h"

#include "math/mod/log.h"

namespace math {

TEST(LogModTest, exist) {
  LogMod<> logMod(100003);
  bool exist;

  EXPECT_EQ(9, logMod.calc(5, 33, 58, exist));
  EXPECT_TRUE(exist);

  EXPECT_EQ(4, logMod.calc(3, 13, 17, exist));
  EXPECT_TRUE(exist);

  EXPECT_EQ(0, logMod.calc(3, 1, 17, exist));
  EXPECT_TRUE(exist);

  EXPECT_EQ(2, logMod.calc(6, 36, 218, exist));
  EXPECT_TRUE(exist);
}

TEST(LogModTest, notExist) {
  LogMod<> logMod(100003);
  bool exist;

  exist = true;
  logMod.calc(2, 3, 4, exist);
  EXPECT_FALSE(exist);

  exist = true;
  logMod.calc(2, 3, 7, exist);
  EXPECT_FALSE(exist);
}

} // namespace math
