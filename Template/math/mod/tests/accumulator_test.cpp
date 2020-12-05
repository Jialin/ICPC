#include "gtest/gtest.h"

#include "math/mod/accumulator.h"

namespace math {

TEST(AccumulatorMod, small) {
  AccumulatorMod<int> acc(10);
  acc.reset(128438);
  EXPECT_EQ(2147355209, acc._invV);
  EXPECT_EQ(8, acc.get());
  acc.add(354553);
  EXPECT_EQ(2147000656, acc._invV);
  EXPECT_EQ(1, acc.get());
  acc.add(32848831);
  EXPECT_EQ(2114151825, acc._invV);
  EXPECT_EQ(2, acc.get());
  acc.add(2114151827);
  EXPECT_EQ(2147483638, acc._invV);
  EXPECT_EQ(9, acc.get());
}

TEST(AccumulatorMod, large) {
  AccumulatorMod<int64_t> acc(1000000007);
  acc.reset(1384823048284824919);
  EXPECT_EQ(7838548988569950888, acc._invV);
  EXPECT_EQ(591063653, acc.get());
  acc.add(3848942848239349238);
  EXPECT_EQ(3989606140330601650, acc._invV);
  EXPECT_EQ(887813144, acc.get());
  acc.add(7);
  EXPECT_EQ(3989606140330601643, acc._invV);
  EXPECT_EQ(887813151, acc.get());
  acc.add(8823838198194141433);
  EXPECT_EQ(9223372036539688182, acc._invV);
  EXPECT_EQ(315087625, acc.get());
}

} // namespace math