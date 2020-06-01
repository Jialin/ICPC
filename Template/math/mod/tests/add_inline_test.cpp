#include "gtest/gtest.h"

#include "math/mod/add_inline.h"

namespace math {

TEST(AddMod, test) {
  int res;

  res = 2;
  addModInline(res, 1, 4);
  EXPECT_EQ(res, 3);

  res = 2;
  addModInline(res, 2, 4);
  EXPECT_EQ(res, 0);

  res = 2;
  addModInline(res, 3, 4);
  EXPECT_EQ(res, 1);

  res = 2;
  addModInline(res, 4, 4);
  EXPECT_EQ(res, 2);

  res = 2;
  addModInline(res, 5, 4);
  EXPECT_EQ(res, 3);
}

TEST(AddMod, testOverflow) {
  int res;

  res = 2147483647;
  addModInline(res, 2147483647, 2147483646);
  EXPECT_EQ(res, 2);
}

} // namespace math
