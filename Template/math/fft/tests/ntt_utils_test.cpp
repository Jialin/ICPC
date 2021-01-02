#include "gtest/gtest.h"

#define NTT_UTILS_ALL
#include "math/fft/ntt_utils_macros.h"

#include "math/fft/ntt_utils.h"

namespace math {

TEST(NTTUtilsTest, bigint) {
  NTTUtils<> ntt(7340033, 5);

  vector<int> x = {1, 2};
  vector<int> y = {3, 4};
  const auto& res1 = ntt.mulModify(x, y);
  ASSERT_EQ(3, res1.size());
  EXPECT_EQ(3, res1[0]);
  EXPECT_EQ(10, res1[1]);
  EXPECT_EQ(8, res1[2]);

  x = {31772, 371773, 371721, 81631};
  y = {348484, 28481838, 381872, 59492};
  const auto& res2 = ntt.mulModify(x, y);
  ASSERT_EQ(7, res2.size());
  EXPECT_EQ(3263884, res2[0]);
  EXPECT_EQ(7008180, res2[1]);
  EXPECT_EQ(4393991, res2[2]);
  EXPECT_EQ(4045475, res2[3]);
  EXPECT_EQ(4368242, res2[4]);
  EXPECT_EQ(5719417, res2[5]);
  EXPECT_EQ(4629639, res2[6]);
}

} // namespace math
