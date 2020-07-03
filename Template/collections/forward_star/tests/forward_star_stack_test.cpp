#include "gtest/gtest.h"

#include "collections/forward_star/forward_star_stack.h"

namespace collections {

TEST(ForwardStarStacks, test) {
  ForwardStarStacks<> fss(3);

  fss.push(0, 3);
  fss.push(1, 100);
  fss.push(0, 2);
  EXPECT_FALSE(fss.empty(0));
  EXPECT_EQ(fss.top(0), 2);
  EXPECT_FALSE(fss.empty(1));
  EXPECT_EQ(fss.top(1), 100);
  EXPECT_TRUE(fss.empty(2));

  fss.push(2, 200);
  fss.push(0, 1);
  fss.push(1, 101);
  EXPECT_FALSE(fss.empty(0));
  EXPECT_EQ(fss.top(0), 1);
  EXPECT_FALSE(fss.empty(1));
  EXPECT_EQ(fss.top(1), 101);
  EXPECT_FALSE(fss.empty(2));
  EXPECT_EQ(fss.top(2), 200);

  fss.pop(2);
  fss.pop(1);
  EXPECT_FALSE(fss.empty(0));
  EXPECT_EQ(fss.top(0), 1);
  EXPECT_FALSE(fss.empty(1));
  EXPECT_EQ(fss.top(1), 100);
  EXPECT_TRUE(fss.empty(2));
}

} // namespace collections
