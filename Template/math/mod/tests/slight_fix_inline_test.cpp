#include "gtest/gtest.h"

#include "math/mod/slight_fix_inline.h"

namespace math {

TEST(SlightFixInline, testTooSmall) {
  int v;

  v = -1;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 2);

  v = -2;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 1);

  v = -3;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 0);

  v = -4;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, -1);

  v = -5;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, -2);
}

TEST(SlightFixInline, testNoChange) {
  int v;

  v = 0;
  slightFixModInline(v, 4);
  EXPECT_EQ(v, 0);

  v = 1;
  slightFixModInline(v, 4);
  EXPECT_EQ(v, 1);

  v = 2;
  slightFixModInline(v, 4);
  EXPECT_EQ(v, 2);

  v = 3;
  slightFixModInline(v, 4);
  EXPECT_EQ(v, 3);
}

TEST(SlightFixInline, testTooBig) {
  int v;

  v = 3;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 0);

  v = 4;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 1);

  v = 5;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 2);

  v = 6;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 3);

  v = 7;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 4);

  v = 8;
  slightFixModInline(v, 3);
  EXPECT_EQ(v, 5);
}

} // namespace math
