#include "gtest/gtest.h"

#include "math/prime/phi_inv64.h"

namespace math {

TEST(PhiInv64Test, basic) {
  PhiInv64 phiInv;
  vector<uint64_t> vs;
  auto processor = [&vs](uint64_t v) { vs.push_back(v); };

  phiInv.calc(1, processor);
  sort(vs.begin(), vs.end());
  ASSERT_EQ(vs.size(), 2);
  EXPECT_EQ(vs[0], 1);
  EXPECT_EQ(vs[1], 2);

  vs.clear();
  phiInv.calc(2, processor);
  sort(vs.begin(), vs.end());
  ASSERT_EQ(vs.size(), 3);
  EXPECT_EQ(vs[0], 3);
  EXPECT_EQ(vs[1], 4);
  EXPECT_EQ(vs[2], 6);

  vs.clear();
  phiInv.calc(15, processor);
  EXPECT_TRUE(vs.empty());

  vs.clear();
  phiInv.calc(8, processor);
  ASSERT_EQ(vs.size(), 5);
  sort(vs.begin(), vs.end());
  EXPECT_EQ(vs[0], 15);
  EXPECT_EQ(vs[1], 16);
  EXPECT_EQ(vs[2], 20);
  EXPECT_EQ(vs[3], 24);
  EXPECT_EQ(vs[4], 30);

  vs.clear();
  phiInv.calc(10, processor);
  ASSERT_EQ(vs.size(), 2);
  sort(vs.begin(), vs.end());
  EXPECT_EQ(vs[0], 11);
  EXPECT_EQ(vs[1], 22);

  vs.clear();
  phiInv.calc(20, processor);
  ASSERT_EQ(vs.size(), 5);
  sort(vs.begin(), vs.end());
  EXPECT_EQ(vs[0], 25);
  EXPECT_EQ(vs[1], 33);
  EXPECT_EQ(vs[2], 44);
  EXPECT_EQ(vs[3], 50);
  EXPECT_EQ(vs[4], 66);

  vs.clear();
  phiInv.calc(30, processor);
  ASSERT_EQ(vs.size(), 2);
  sort(vs.begin(), vs.end());
  EXPECT_EQ(vs[0], 31);
  EXPECT_EQ(vs[1], 62);

  vs.clear();
  phiInv.calc(40, processor);
  ASSERT_EQ(vs.size(), 9);
  sort(vs.begin(), vs.end());
  EXPECT_EQ(vs[0], 41);
  EXPECT_EQ(vs[1], 55);
  EXPECT_EQ(vs[2], 75);
  EXPECT_EQ(vs[3], 82);
  EXPECT_EQ(vs[4], 88);
  EXPECT_EQ(vs[5], 100);
  EXPECT_EQ(vs[6], 110);
  EXPECT_EQ(vs[7], 132);
  EXPECT_EQ(vs[8], 150);

  vs.clear();
  phiInv.calc(50, processor);
  ASSERT_TRUE(vs.empty());
}

} // namespace math
