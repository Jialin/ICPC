#include "gtest/gtest.h"

#define MOD_INT_DIV_INLINE
#define NTT_ONLINE_UTILS_ALL
#include "math/fft/ntt_online_utils_macros.h"

#include "math/fft/ntt_online_utils.h"

using namespace std;

namespace math {

TEST(NTTOnlineUtilsTest, onlineInlineModInt) {
  const int MOD = 924844033;
  auto& ntt = NTTOnlineUtils<int, int64_t, MOD, 3597>::instance();
  vector<ModInt<int, int64_t, MOD>> fs;
  fs.resize(1);
  fs.assign(1, 1);
  ntt.onlineInlineModInt(
      fs,
      {0, 0, 2, 9, 616562726, 693633181, 739875896, 161850647, 346462722, 125987923},
      1,
      10,
      [](ModInt<int, int64_t, MOD>& f, int idx) {
        f /= idx;
      });
  ASSERT_GE(fs.size(), 10);
  EXPECT_EQ(1, fs[0]._v);
  EXPECT_EQ(0, fs[1]._v);
  EXPECT_EQ(1, fs[2]._v);
  EXPECT_EQ(3, fs[3]._v);
  EXPECT_EQ(154140682, fs[4]._v);
  EXPECT_EQ(693633059, fs[5]._v);
  EXPECT_EQ(739875352, fs[6]._v);
  EXPECT_EQ(254332590, fs[7]._v);
  EXPECT_EQ(76705244, fs[8]._v);
  EXPECT_EQ(34551843, fs[9]._v);

  fs.resize(1);
  fs.assign(1, 1);
  ntt.onlineInlineModInt(
      fs,
      {0, 1, 1, 462422018, 308281347, 732168198, 369937624, 52664753, 358193614, 161641386},
      1,
      10,
      [](ModInt<int, int64_t, MOD>& f, int idx) {
        f /= idx;
      });
  ASSERT_GE(fs.size(), 10);
  EXPECT_EQ(1, fs[0]._v);
  EXPECT_EQ(1, fs[1]._v);
  EXPECT_EQ(1, fs[2]._v);
  EXPECT_EQ(770703362, fs[3]._v);
  EXPECT_EQ(385351682, fs[4]._v);
  EXPECT_EQ(716754128, fs[5]._v);
  EXPECT_EQ(303143326, fs[6]._v);
  EXPECT_EQ(246441582, fs[7]._v);
  EXPECT_EQ(612984437, fs[8]._v);
  EXPECT_EQ(547380366, fs[9]._v);
}

} // namespace math
