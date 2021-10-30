#include "gtest/gtest.h"

#define BASE_SLIDING_WINDOW_ALL
#include "ds/sliding_window/base_sliding_window_macros.h"

#include "ds/sliding_window/min_sliding_window.h"

namespace ds {

TEST(MinSlidingWindowTest, basic) {
  MinSlidingWindow<int> sw;
  sw.init(3);

  sw.push_back(0, 4);
  EXPECT_EQ(0, sw.calc().first);
  EXPECT_EQ(4, sw.calc().second);

  sw.push_back(1, 3);
  EXPECT_EQ(1, sw.calc().first);
  EXPECT_EQ(3, sw.calc().second);

  sw.push_back(2, 5);
  EXPECT_EQ(1, sw.calc().first);
  EXPECT_EQ(3, sw.calc().second);

  sw.push_back(3, 2);
  EXPECT_EQ(3, sw.calc().first);
  EXPECT_EQ(2, sw.calc().second);

  sw.push_back(4, 1);
  EXPECT_EQ(4, sw.calc().first);
  EXPECT_EQ(1, sw.calc().second);

  sw.push_back(5, 0);
  EXPECT_EQ(5, sw.calc().first);
  EXPECT_EQ(0, sw.calc().second);

  sw.push_back(6, 2);
  EXPECT_EQ(5, sw.calc().first);
  EXPECT_EQ(0, sw.calc().second);
}

} // namespace ds
