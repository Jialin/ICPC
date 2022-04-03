#include "gtest/gtest.h"

#define BASE_FENWICK_ALL
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"

using namespace std;

namespace ds {

TEST(FenwickSum, initAll) {
  ds::FenwickSum<int> fen;
  fen.initAll({0, 20, 0, 30, 40});
  EXPECT_EQ(0, fen.calcRange(0, 1));
  EXPECT_EQ(20, fen.calcRange(0, 2));
  EXPECT_EQ(20, fen.calcRange(0, 3));
  EXPECT_EQ(50, fen.calcRange(0, 4));
  EXPECT_EQ(90, fen.calcRange(0, 5));
  EXPECT_EQ(20, fen.calcRange(1, 2));
  EXPECT_EQ(20, fen.calcRange(1, 3));
  EXPECT_EQ(50, fen.calcRange(1, 4));
  EXPECT_EQ(90, fen.calcRange(1, 5));
  EXPECT_EQ(0, fen.calcRange(2, 3));
  EXPECT_EQ(30, fen.calcRange(2, 4));
  EXPECT_EQ(70, fen.calcRange(2, 5));
  EXPECT_EQ(30, fen.calcRange(3, 4));
  EXPECT_EQ(70, fen.calcRange(3, 5));
  EXPECT_EQ(40, fen.calcRange(4, 5));
}

TEST(FenwickSum, calcRange) {
  ds::FenwickSum<int> fen;
  fen.init(5);

  EXPECT_EQ(0, fen.calcRange(0, 1));
  EXPECT_EQ(0, fen.calcRange(0, 2));
  EXPECT_EQ(0, fen.calcRange(0, 3));
  EXPECT_EQ(0, fen.calcRange(0, 4));
  EXPECT_EQ(0, fen.calcRange(0, 5));
  EXPECT_EQ(0, fen.calcRange(1, 2));
  EXPECT_EQ(0, fen.calcRange(1, 3));
  EXPECT_EQ(0, fen.calcRange(1, 4));
  EXPECT_EQ(0, fen.calcRange(1, 5));
  EXPECT_EQ(0, fen.calcRange(2, 3));
  EXPECT_EQ(0, fen.calcRange(2, 4));
  EXPECT_EQ(0, fen.calcRange(2, 5));
  EXPECT_EQ(0, fen.calcRange(3, 4));
  EXPECT_EQ(0, fen.calcRange(3, 5));
  EXPECT_EQ(0, fen.calcRange(4, 5));

  fen.update(1, 20);
  fen.update(3, 30);
  fen.update(4, 40);
  EXPECT_EQ(0, fen.calcRange(0, 1));
  EXPECT_EQ(20, fen.calcRange(0, 2));
  EXPECT_EQ(20, fen.calcRange(0, 3));
  EXPECT_EQ(50, fen.calcRange(0, 4));
  EXPECT_EQ(90, fen.calcRange(0, 5));
  EXPECT_EQ(20, fen.calcRange(1, 2));
  EXPECT_EQ(20, fen.calcRange(1, 3));
  EXPECT_EQ(50, fen.calcRange(1, 4));
  EXPECT_EQ(90, fen.calcRange(1, 5));
  EXPECT_EQ(0, fen.calcRange(2, 3));
  EXPECT_EQ(30, fen.calcRange(2, 4));
  EXPECT_EQ(70, fen.calcRange(2, 5));
  EXPECT_EQ(30, fen.calcRange(3, 4));
  EXPECT_EQ(70, fen.calcRange(3, 5));
  EXPECT_EQ(40, fen.calcRange(4, 5));
}

TEST(FenwickSum, calcKth) {
  ds::FenwickSum<int> fen;
  fen.init(5);
  fen.update(0, 1);
  fen.update(1, 2);
  fen.update(2, 1);
  fen.update(3, 0);
  fen.update(4, 3);

  EXPECT_EQ(0, fen.calcKth(0));
  EXPECT_EQ(1, fen.calcKth(1));
  EXPECT_EQ(1, fen.calcKth(2));
  EXPECT_EQ(2, fen.calcKth(3));
  EXPECT_EQ(4, fen.calcKth(4));
  EXPECT_EQ(4, fen.calcKth(5));
  EXPECT_EQ(4, fen.calcKth(6));
  EXPECT_EQ(5, fen.calcKth(7));
}

} // namespace ds
