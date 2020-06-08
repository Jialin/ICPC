#include "gtest/gtest.h"

#include <vector>

#include "math/mod/mod_exp_utils.h"

using namespace std;

namespace math {

TEST(ModExpUtils, test) {
  ModExpUtils<> expUtils(2, 5);
  EXPECT_EQ(expUtils.exp(0), 1);
  EXPECT_EQ(expUtils.exp(3), 3);
  EXPECT_EQ(expUtils.exp(2147483646), 4);
  EXPECT_EQ(expUtils.exp(5), 2);
  EXPECT_EQ(expUtils.exp(123), 3);

  expUtils.init(2, 13);
  EXPECT_EQ(expUtils.exp(2147483647), 11);
  EXPECT_EQ(expUtils.exp(5), 6);
  EXPECT_EQ(expUtils.exp(123), 8);

  expUtils.init(1463, 29478);
  EXPECT_EQ(expUtils.exp(1397372724), 27031);
  EXPECT_EQ(expUtils.exp(12345), 3809);
}

TEST(ModExpUtils, testLargeBase) {
  ModExpUtils<> expUtils(7, 5);
  EXPECT_EQ(expUtils.exp(3), 3);
  EXPECT_EQ(expUtils.exp(2147483646), 4);
  EXPECT_EQ(expUtils.exp(5), 2);
  EXPECT_EQ(expUtils.exp(123), 3);
}

TEST(ExpModQuick, testMod1) {
  ModExpUtils<> expUtils(1, 1);
  EXPECT_EQ(expUtils.exp(0), 0);
  EXPECT_EQ(expUtils.exp(1), 0);

  expUtils.init(3, 1);
  EXPECT_EQ(expUtils.exp(2), 0);
}

} // namespace math
