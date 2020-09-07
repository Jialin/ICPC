#include "gtest/gtest.h"

#include "math/mod/add.h"

namespace math {

TEST(AddMod, test) {
  EXPECT_EQ(addMod(2, 1, 4), 3);
  EXPECT_EQ(addMod(2, 2, 4), 0);
  EXPECT_EQ(addMod(2, 3, 4), 1);
  EXPECT_EQ(addMod(2, 4, 4), 2);
  EXPECT_EQ(addMod(2, 5, 4), 3);
}

TEST(AddMod, testOverflow) {
  int res = addMod<uint32_t>(2147483645, 2147483646, 2147483647);
  EXPECT_EQ(res, 2147483644);

  long long res64 = addMod<long long>(2147483647, 2147483647, 1000000007);
  EXPECT_EQ(res64, 294967266);
}

} // namespace math
