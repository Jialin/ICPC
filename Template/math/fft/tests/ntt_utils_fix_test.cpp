#include "gtest/gtest.h"

#define NTT_UTILS_FIX_ALL
#define MOD_INT_DIV_INLINE
#include "math/fft/ntt_utils_fix_macros.h"

#include "math/fft/ntt_utils_fix.h"

namespace math {

TEST(NTTUtilsFixTest, bigint) {
  NTTUtilsFix<int, int64_t, 7340033, 5> ntt;
  vector<ModInt<int, int64_t, 7340033>> x = {1, 2}, y = {3, 4};
  ntt.mulInlineModify(x, y, false);
  ASSERT_EQ(3, x.size());
  EXPECT_EQ(3, x[0]._v);
  EXPECT_EQ(10, x[1]._v);
  EXPECT_EQ(8, x[2]._v);

  x = {31772, 371773, 371721, 81631};
  y = {348484, 28481838, 381872, 59492};
  ntt.mulInlineModify(x, y, false);
  ASSERT_EQ(7, x.size());
  EXPECT_EQ(3263884, x[0]._v);
  EXPECT_EQ(7008180, x[1]._v);
  EXPECT_EQ(4393991, x[2]._v);
  EXPECT_EQ(4045475, x[3]._v);
  EXPECT_EQ(4368242, x[4]._v);
  EXPECT_EQ(5719417, x[5]._v);
  EXPECT_EQ(4629639, x[6]._v);
}

TEST(NTTUtilsFixTest, recurrenceInlineColorForests) {
  // https://csacademy.com/contest/archive/task/colored-forests/statement/
  static const int MOD = 924844033;
  NTTUtilsFix<int, int64_t, MOD, 3597> ntt;
  vector<ModInt<int, int64_t, MOD>> fs;
  fs.assign(1, 1);
  ntt.recurrenceInline(
      fs,
      {0,
       0,
       2,
       9,
       616562726,
       693633181,
       739875896,
       161850647,
       346462722,
       125987923},
      1,
      10,
      [](ModInt<int, int64_t, MOD>& f, int idx) {
        return f /= idx;
      });

  fs.assign(1, 1);
  ntt.recurrenceInline(
      fs,
      {0,
       1,
       1,
       462422018,
       308281347,
       732168198,
       369937624,
       52664753,
       358193614,
       161641386},
      1,
      10,
      [](ModInt<int, int64_t, MOD>& f, int idx) {
        return f /= idx;
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
