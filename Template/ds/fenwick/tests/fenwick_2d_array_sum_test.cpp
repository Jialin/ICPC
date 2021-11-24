#include "gtest/gtest.h"

#define BASE_FENWICK_2D_ARRAY_ALL
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_sum.h"

using namespace std;

namespace ds {

TEST(Fenwick2DArraySum, basic) {
  ds::Fenwick2DArraySum<int, 3, 4> fen;
  fen.init(3, 4);

  fen.update(1, 2, 10);
  EXPECT_EQ(0, fen.calcPrefix(1, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 3));
  EXPECT_EQ(0, fen.calcPrefix(1, 4));
  EXPECT_EQ(0, fen.calcPrefix(2, 1));
  EXPECT_EQ(0, fen.calcPrefix(2, 2));
  EXPECT_EQ(10, fen.calcPrefix(2, 3));
  EXPECT_EQ(10, fen.calcPrefix(2, 4));
  EXPECT_EQ(0, fen.calcPrefix(3, 1));
  EXPECT_EQ(0, fen.calcPrefix(3, 2));
  EXPECT_EQ(10, fen.calcPrefix(3, 3));
  EXPECT_EQ(10, fen.calcPrefix(3, 4));

  fen.update(0, 3, 20);
  EXPECT_EQ(0, fen.calcPrefix(1, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 3));
  EXPECT_EQ(20, fen.calcPrefix(1, 4));
  EXPECT_EQ(0, fen.calcPrefix(2, 1));
  EXPECT_EQ(0, fen.calcPrefix(2, 2));
  EXPECT_EQ(10, fen.calcPrefix(2, 3));
  EXPECT_EQ(30, fen.calcPrefix(2, 4));
  EXPECT_EQ(0, fen.calcPrefix(3, 1));
  EXPECT_EQ(0, fen.calcPrefix(3, 2));
  EXPECT_EQ(10, fen.calcPrefix(3, 3));
  EXPECT_EQ(30, fen.calcPrefix(3, 4));

  fen.update(1, 0, 40);
  EXPECT_EQ(0, fen.calcPrefix(1, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 3));
  EXPECT_EQ(20, fen.calcPrefix(1, 4));
  EXPECT_EQ(40, fen.calcPrefix(2, 1));
  EXPECT_EQ(40, fen.calcPrefix(2, 2));
  EXPECT_EQ(50, fen.calcPrefix(2, 3));
  EXPECT_EQ(70, fen.calcPrefix(2, 4));
  EXPECT_EQ(40, fen.calcPrefix(3, 1));
  EXPECT_EQ(40, fen.calcPrefix(3, 2));
  EXPECT_EQ(50, fen.calcPrefix(3, 3));
  EXPECT_EQ(70, fen.calcPrefix(3, 4));
}

} // namespace ds
