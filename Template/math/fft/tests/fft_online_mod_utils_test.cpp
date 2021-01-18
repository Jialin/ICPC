#include "gtest/gtest.h"

#define FFT_ONLINE_MOD_UTILS_ALL
#define FFT_POLY_MOD_INT_ASSIGN_VECTOR
#include "math/fft/fft_online_mod_utils_macros.h"
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/fft/fft_online_mod_utils.h"
#include "math/poly/fft_poly_mod_int.h"

using namespace std;

namespace math {

TEST(FFTOnlineModUtilsTest, onlineInlineModInt) {
  const int MOD = 1000000007;
  auto& fft = FFTOnlineModUtils<double>::instance();
  FFTPolyModInt<double, int, int64_t, MOD> bases, res;
  bases = vector<int>{0, 1, 1, 0, 1, 0, 2, 0, 5};
  res = vector<int>{1};
  fft.onlineInlineModInt<int, int64_t, MOD>(
      res, bases, 1, 10000, [](ModInt<int, int64_t, MOD>& f, int idx) {});
  ASSERT_GE(10000, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(1, res[1]._v);
  EXPECT_EQ(2, res[2]._v);
  EXPECT_EQ(3, res[3]._v);
  EXPECT_EQ(6, res[4]._v);
  EXPECT_EQ(10, res[5]._v);
  EXPECT_EQ(20, res[6]._v);
  EXPECT_EQ(35, res[7]._v);
  EXPECT_EQ(50622761, res[1024]._v);
  EXPECT_EQ(294060367, res[1025]._v);
  EXPECT_EQ(600102449, res[2048]._v);
  EXPECT_EQ(894517855, res[2049]._v);
  EXPECT_EQ(200542943, res[4096]._v);
  EXPECT_EQ(911015404, res[4097]._v);
}

} // namespace math
