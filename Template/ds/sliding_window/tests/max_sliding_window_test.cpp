#include "gtest/gtest.h"

#define BASE_SLIDING_WINDOW_ALL
#include "ds/sliding_window/base_sliding_window_macros.h"

#include "ds/sliding_window/max_sliding_window.h"

namespace ds {

TEST(MaxSlidingWindowTest, basic) {
  MaxSlidingWindow<int> sw;
  sw.init(3);

  sw.push_back(0, 4);
  EXPECT_EQ(0, sw.get().first);
  EXPECT_EQ(4, sw.get().second);

  sw.push_back(1, 3);
  EXPECT_EQ(0, sw.get().first);
  EXPECT_EQ(4, sw.get().second);

  sw.push_back(2, 5);
  EXPECT_EQ(2, sw.get().first);
  EXPECT_EQ(5, sw.get().second);

  sw.push_back(3, 2);
  EXPECT_EQ(2, sw.get().first);
  EXPECT_EQ(5, sw.get().second);

  sw.push_back(4, 1);
  EXPECT_EQ(2, sw.get().first);
  EXPECT_EQ(5, sw.get().second);

  sw.push_back(5, 0);
  EXPECT_EQ(3, sw.get().first);
  EXPECT_EQ(2, sw.get().second);

  sw.push_back(6, 2);
  EXPECT_EQ(6, sw.get().first);
  EXPECT_EQ(2, sw.get().second);
}

} // namespace ds
