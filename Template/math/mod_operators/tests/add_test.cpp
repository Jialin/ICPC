#include "gtest/gtest.h"

#include "math/mod_operators/add.h"

namespace math {

TEST(AddMod, test) {
  EXPECT_EQ(addMod(2, 3, 4), 1);
  EXPECT_EQ(addMod(2, 3, 5), 0);
  EXPECT_EQ(addMod(2, 3, 6), 5);
}

TEST(AddMod, testOverflow) {
  int64_t res = addMod<int32_t, int64_t>(2147483647, 2147483647, 1000000007);
  EXPECT_EQ(res, 294967266);
}

} // namespace math
