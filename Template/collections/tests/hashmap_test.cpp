#include "gtest/gtest.h"

#include "collections/hashmap.h"

namespace collections {

TEST(HashmapTest, basic) {
  Hashmap<int, int> hmap(7);
  EXPECT_EQ(hmap._vs._edgeIdx, 0);

  hmap.set(1, 10);
  hmap.set(2, 20);
  EXPECT_EQ(hmap._vs._edgeIdx, 2);
  EXPECT_FALSE(hmap.getPtr(0));
  EXPECT_EQ(*hmap.getPtr(1), 10);
  EXPECT_EQ(*hmap.getPtr(2), 20);
  EXPECT_FALSE(hmap.getPtr(3));
  EXPECT_FALSE(hmap.getPtr(7));

  hmap.set(1, 30);
  hmap.set(0, 40);
  EXPECT_EQ(hmap._vs._edgeIdx, 3);
  EXPECT_EQ(*hmap.getPtr(0), 40);
  EXPECT_EQ(*hmap.getPtr(1), 30);
  EXPECT_EQ(*hmap.getPtr(2), 20);
  EXPECT_FALSE(hmap.getPtr(3));
  EXPECT_FALSE(hmap.getPtr(7));

  hmap.set(3, 50);
  hmap.set(7, 60);
  EXPECT_EQ(hmap._vs._edgeIdx, 5);
  EXPECT_EQ(*hmap.getPtr(0), 40);
  EXPECT_EQ(*hmap.getPtr(1), 30);
  EXPECT_EQ(*hmap.getPtr(2), 20);
  EXPECT_EQ(*hmap.getPtr(3), 50);
  EXPECT_EQ(*hmap.getPtr(7), 60);
}

} // namespace collections
