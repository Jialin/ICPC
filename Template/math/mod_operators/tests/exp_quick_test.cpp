#include "gtest/gtest.h"

#include <vector>

#include "math/mod_operators/exp_quick.h"

using namespace std;

namespace math {

TEST(ExpModQuick, test) {
  vector<int32_t> powList;

  powList.clear();
  EXPECT_EQ(expModQuick(powList, 2, 3, 5), 3);
  EXPECT_EQ(expModQuick(powList, 2, 2147483646, 5), 4);

  powList.clear();
  EXPECT_EQ(expModQuick(powList, 2, 2147483647, 13), 11);

  powList.clear();
  EXPECT_EQ(expModQuick(powList, 1463, 1397372724, 29478), 27031);
}

TEST(ExpModQuick, testMod1) {
  vector<int32_t> powList;

  powList.clear();
  EXPECT_EQ(expModQuick(powList, 1, 1, 1), 0);

  powList.clear();
  EXPECT_EQ(expModQuick(powList, 3, 2, 1), 0);
}

} // namespace math
