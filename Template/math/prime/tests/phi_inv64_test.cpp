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
}

} // namespace math
