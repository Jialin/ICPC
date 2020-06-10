#include "gtest/gtest.h"

#include "collections/bitset.h"

namespace collections {

TEST(Bitset, testInitZero) {
  Bitset bs(5);
  EXPECT_FALSE(bs.test(0));
  EXPECT_FALSE(bs.test(1));
  EXPECT_FALSE(bs.test(2));
  EXPECT_FALSE(bs.test(3));
  EXPECT_FALSE(bs.test(4));
  bs.set(0);
  bs.set(1);
  bs.set(3);
  EXPECT_TRUE(bs.test(0));
  EXPECT_TRUE(bs.test(1));
  EXPECT_FALSE(bs.test(2));
  EXPECT_TRUE(bs.test(3));
  EXPECT_FALSE(bs.test(4));
  bs.set(0, false);
  bs.set(1, false);
  bs.set(3);
  EXPECT_FALSE(bs.test(0));
  EXPECT_FALSE(bs.test(1));
  EXPECT_FALSE(bs.test(2));
  EXPECT_TRUE(bs.test(3));
  EXPECT_FALSE(bs.test(4));
}

TEST(Bitset, testInitOne) {
  Bitset bs(5, false);
  EXPECT_TRUE(bs.test(0));
  EXPECT_TRUE(bs.test(1));
  EXPECT_TRUE(bs.test(2));
  EXPECT_TRUE(bs.test(3));
  EXPECT_TRUE(bs.test(4));
  bs.set(0, false);
  bs.set(2, false);
  bs.set(4, false);
  EXPECT_FALSE(bs.test(0));
  EXPECT_TRUE(bs.test(1));
  EXPECT_FALSE(bs.test(2));
  EXPECT_TRUE(bs.test(3));
  EXPECT_FALSE(bs.test(4));
  bs.set(0);
  bs.set(1);
  bs.set(3);
  EXPECT_TRUE(bs.test(0));
  EXPECT_TRUE(bs.test(1));
  EXPECT_FALSE(bs.test(2));
  EXPECT_TRUE(bs.test(3));
  EXPECT_FALSE(bs.test(4));
}

} // namespace collections
