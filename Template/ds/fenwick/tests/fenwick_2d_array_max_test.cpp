#include "gtest/gtest.h"

#define BASE_FENWICK_2D_ARRAY_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_max.h"

using namespace std;

namespace ds {

TEST(Fenwick2DArrayMax, basic) {
  ds::Fenwick2DArrayMax<int, 3, 4> fen;
  fen.init(3, 4);

  fen.update(1, 2, 10);
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 1));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 2));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 3));
  EXPECT_EQ(-2147483648, fen.calcPrefix(1, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(1, 1));
  EXPECT_EQ(10, fen.calcPrefix(1, 2));
  EXPECT_EQ(10, fen.calcPrefix(1, 3));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 1));
  EXPECT_EQ(10, fen.calcPrefix(2, 2));
  EXPECT_EQ(10, fen.calcPrefix(2, 3));

  fen.update(0, 3, 20);
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 1));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 2));
  EXPECT_EQ(20, fen.calcPrefix(0, 3));
  EXPECT_EQ(-2147483648, fen.calcPrefix(1, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(1, 1));
  EXPECT_EQ(10, fen.calcPrefix(1, 2));
  EXPECT_EQ(20, fen.calcPrefix(1, 3));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 1));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 2));
  EXPECT_EQ(20, fen.calcPrefix(2, 3));

  fen.update(1, 0, 15);
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 1));
  EXPECT_EQ(-2147483648, fen.calcPrefix(0, 2));
  EXPECT_EQ(20, fen.calcPrefix(0, 3));
  EXPECT_EQ(15, fen.calcPrefix(1, 0));
  EXPECT_EQ(15, fen.calcPrefix(1, 1));
  EXPECT_EQ(20, fen.calcPrefix(1, 2));
  EXPECT_EQ(20, fen.calcPrefix(1, 3));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 1));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2, 2));
  EXPECT_EQ(20, fen.calcPrefix(2, 3));
}

} // namespace ds
