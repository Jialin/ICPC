#include "gtest/gtest.h"

#define BASE_FENWICK_3D_ARRAY_ALL
#include "ds/fenwick/base_fenwick_3d_array_macros.h"

#include "ds/fenwick/fenwick_3d_array_sum.h"

using namespace std;

namespace ds {

TEST(Fenwick3DArraySum, basic) {
  ds::Fenwick3DArraySum<int, 2, 3, 2> fen;
  fen.init(2, 3, 2);

  fen.update(1, 1, 1, 10);
  EXPECT_EQ(0, fen.calcPrefix(1, 1, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 1, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 2, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 2, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 3, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 3, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 1, 1));
  EXPECT_EQ(0, fen.calcPrefix(2, 1, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 2, 1));
  EXPECT_EQ(10, fen.calcPrefix(2, 2, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 3, 1));
  EXPECT_EQ(10, fen.calcPrefix(2, 3, 2));

  fen.update(0, 2, 0, 20);
  EXPECT_EQ(0, fen.calcPrefix(1, 1, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 1, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 2, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 2, 2));
  EXPECT_EQ(20, fen.calcPrefix(1, 3, 1));
  EXPECT_EQ(20, fen.calcPrefix(1, 3, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 1, 1));
  EXPECT_EQ(0, fen.calcPrefix(2, 1, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 2, 1));
  EXPECT_EQ(10, fen.calcPrefix(2, 2, 2));
  EXPECT_EQ(20, fen.calcPrefix(2, 3, 1));
  EXPECT_EQ(30, fen.calcPrefix(2, 3, 2));

  fen.update(0, 1, 1, 40);
  EXPECT_EQ(0, fen.calcPrefix(1, 1, 1));
  EXPECT_EQ(0, fen.calcPrefix(1, 1, 2));
  EXPECT_EQ(0, fen.calcPrefix(1, 2, 1));
  EXPECT_EQ(40, fen.calcPrefix(1, 2, 2));
  EXPECT_EQ(20, fen.calcPrefix(1, 3, 1));
  EXPECT_EQ(60, fen.calcPrefix(1, 3, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 1, 1));
  EXPECT_EQ(0, fen.calcPrefix(2, 1, 2));
  EXPECT_EQ(0, fen.calcPrefix(2, 2, 1));
  EXPECT_EQ(50, fen.calcPrefix(2, 2, 2));
  EXPECT_EQ(20, fen.calcPrefix(2, 3, 1));
  EXPECT_EQ(70, fen.calcPrefix(2, 3, 2));
}

} // namespace ds
