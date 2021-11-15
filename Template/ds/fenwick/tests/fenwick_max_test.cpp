#include "gtest/gtest.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_max.h"

using namespace std;

namespace ds {

TEST(FenwickMax, basic) {
  ds::FenwickMax<int> fen;
  fen.init(5);

  EXPECT_EQ(-2147483648, fen.calcPrefix(0));
  EXPECT_EQ(-2147483648, fen.calcPrefix(1));
  EXPECT_EQ(-2147483648, fen.calcPrefix(2));
  EXPECT_EQ(-2147483648, fen.calcPrefix(3));
  EXPECT_EQ(-2147483648, fen.calcPrefix(4));

  fen.update(1, 20);
  EXPECT_EQ(-2147483648, fen.calcPrefix(0));
  EXPECT_EQ(20, fen.calcPrefix(1));
  EXPECT_EQ(20, fen.calcPrefix(2));
  EXPECT_EQ(20, fen.calcPrefix(3));
  EXPECT_EQ(20, fen.calcPrefix(4));

  fen.update(3, 30);
  EXPECT_EQ(-2147483648, fen.calcPrefix(0));
  EXPECT_EQ(20, fen.calcPrefix(1));
  EXPECT_EQ(20, fen.calcPrefix(2));
  EXPECT_EQ(30, fen.calcPrefix(3));
  EXPECT_EQ(30, fen.calcPrefix(4));

  fen.update(4, 40);
  EXPECT_EQ(-2147483648, fen.calcPrefix(0));
  EXPECT_EQ(20, fen.calcPrefix(1));
  EXPECT_EQ(20, fen.calcPrefix(2));
  EXPECT_EQ(30, fen.calcPrefix(3));
  EXPECT_EQ(40, fen.calcPrefix(4));
}

} // namespace ds
