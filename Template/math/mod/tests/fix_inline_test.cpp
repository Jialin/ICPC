#include "gtest/gtest.h"

#include "math/mod/fix_inline.h"

namespace math {

TEST(FixInline, testTooSmall) {
  int v;

  v = -1;
  fixModInline(v, 3);
  EXPECT_EQ(v, 2);

  v = -2;
  fixModInline(v, 3);
  EXPECT_EQ(v, 1);

  v = -3;
  fixModInline(v, 3);
  EXPECT_EQ(v, 0);

  v = -4;
  fixModInline(v, 3);
  EXPECT_EQ(v, 2);

  v = -5;
  fixModInline(v, 3);
  EXPECT_EQ(v, 1);

  v = -6;
  fixModInline(v, 3);
  EXPECT_EQ(v, 0);
}

TEST(FixInline, testNoChange) {
  int v;

  v = 0;
  fixModInline(v, 4);
  EXPECT_EQ(v, 0);

  v = 1;
  fixModInline(v, 4);
  EXPECT_EQ(v, 1);

  v = 2;
  fixModInline(v, 4);
  EXPECT_EQ(v, 2);

  v = 3;
  fixModInline(v, 4);
  EXPECT_EQ(v, 3);
}

TEST(FixInline, testTooBig) {
  int v;

  v = 3;
  fixModInline(v, 3);
  EXPECT_EQ(v, 0);

  v = 4;
  fixModInline(v, 3);
  EXPECT_EQ(v, 1);

  v = 5;
  fixModInline(v, 3);
  EXPECT_EQ(v, 2);

  v = 6;
  fixModInline(v, 3);
  EXPECT_EQ(v, 0);

  v = 7;
  fixModInline(v, 3);
  EXPECT_EQ(v, 1);

  v = 8;
  fixModInline(v, 3);
  EXPECT_EQ(v, 2);
}

} // namespace math
