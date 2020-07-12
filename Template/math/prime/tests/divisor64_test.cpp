#include "gtest/gtest.h"

#include "math/prime/divisor64.h"

namespace math {

TEST(DivisorIterator64, testSmall) {
  vector<int> ds;
  auto processor = [&ds](int d) {
    ds.push_back(d);
    return true;
  };

  divisorIterator64(4, processor);
  sort(ds.begin(), ds.end());
  ASSERT_EQ(ds.size(), 3);
  EXPECT_EQ(ds[0], 1);
  EXPECT_EQ(ds[1], 2);
  EXPECT_EQ(ds[2], 4);

  ds.clear();
  divisorIterator64(5, processor);
  sort(ds.begin(), ds.end());
  ASSERT_EQ(ds.size(), 2);
  EXPECT_EQ(ds[0], 1);
  EXPECT_EQ(ds[1], 5);

  ds.clear();
  divisorIterator64(11, processor);
  sort(ds.begin(), ds.end());
  ASSERT_EQ(ds.size(), 2);
  EXPECT_EQ(ds[0], 1);
  EXPECT_EQ(ds[1], 11);
}

TEST(DivisorIterator64, testLarge) {
  vector<int> ds;
  auto processor = [&ds](int d) {
    ds.push_back(d);
    return true;
  };

  divisorIterator64(123456, processor);
  sort(ds.begin(), ds.end());
  ASSERT_EQ(ds.size(), 28);
  EXPECT_EQ(ds[0], 1);
  EXPECT_EQ(ds[1], 2);
  EXPECT_EQ(ds[2], 3);
  EXPECT_EQ(ds[3], 4);
  EXPECT_EQ(ds[4], 6);
  EXPECT_EQ(ds[5], 8);
  EXPECT_EQ(ds[6], 12);
  EXPECT_EQ(ds[7], 16);
  EXPECT_EQ(ds[8], 24);
  EXPECT_EQ(ds[9], 32);
  EXPECT_EQ(ds[10], 48);
  EXPECT_EQ(ds[11], 64);
  EXPECT_EQ(ds[12], 96);
  EXPECT_EQ(ds[13], 192);
  EXPECT_EQ(ds[14], 643);
  EXPECT_EQ(ds[15], 1286);
  EXPECT_EQ(ds[16], 1929);
  EXPECT_EQ(ds[17], 2572);
  EXPECT_EQ(ds[18], 3858);
  EXPECT_EQ(ds[19], 5144);
  EXPECT_EQ(ds[20], 7716);
  EXPECT_EQ(ds[21], 10288);
  EXPECT_EQ(ds[22], 15432);
  EXPECT_EQ(ds[23], 20576);
  EXPECT_EQ(ds[24], 30864);
  EXPECT_EQ(ds[25], 41152);
  EXPECT_EQ(ds[26], 61728);
  EXPECT_EQ(ds[27], 123456);

  ds.clear();
  divisorIterator64(987654, processor);
  sort(ds.begin(), ds.end());
  ASSERT_EQ(ds.size(), 16);
  EXPECT_EQ(ds[0], 1);
  EXPECT_EQ(ds[1], 2);
  EXPECT_EQ(ds[2], 3);
  EXPECT_EQ(ds[3], 6);
  EXPECT_EQ(ds[4], 97);
  EXPECT_EQ(ds[5], 194);
  EXPECT_EQ(ds[6], 291);
  EXPECT_EQ(ds[7], 582);
  EXPECT_EQ(ds[8], 1697);
  EXPECT_EQ(ds[9], 3394);
  EXPECT_EQ(ds[10], 5091);
  EXPECT_EQ(ds[11], 10182);
  EXPECT_EQ(ds[12], 164609);
  EXPECT_EQ(ds[13], 329218);
  EXPECT_EQ(ds[14], 493827);
  EXPECT_EQ(ds[15], 987654);
}

} // namespace math
