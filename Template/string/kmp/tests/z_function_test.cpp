#include "gtest/gtest.h"

#define Z_FUNCTION_ALL
#include "string/kmp/z_function_macros.h"

#include "string/kmp/z_function.h"

namespace str {

TEST(ZFunctionTest, basic) {
  ZFunction<char> zfun;

  zfun.init(5, "babab");
  EXPECT_EQ(5, zfun._prefixs.size());
  EXPECT_EQ(5, zfun._prefixs[0]);
  EXPECT_EQ(0, zfun._prefixs[1]);
  EXPECT_EQ(3, zfun._prefixs[2]);
  EXPECT_EQ(0, zfun._prefixs[3]);
  EXPECT_EQ(1, zfun._prefixs[4]);

  zfun.init(9, "azbazbzaz");
  EXPECT_EQ(9, zfun._prefixs.size());
  EXPECT_EQ(9, zfun._prefixs[0]);
  EXPECT_EQ(0, zfun._prefixs[1]);
  EXPECT_EQ(0, zfun._prefixs[2]);
  EXPECT_EQ(3, zfun._prefixs[3]);
  EXPECT_EQ(0, zfun._prefixs[4]);
  EXPECT_EQ(0, zfun._prefixs[5]);
  EXPECT_EQ(0, zfun._prefixs[6]);
  EXPECT_EQ(2, zfun._prefixs[7]);
  EXPECT_EQ(0, zfun._prefixs[8]);
}

} // namespace str
