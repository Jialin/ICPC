#include "gtest/gtest.h"

#include "math/prime/factorize32.h"

namespace math {

TEST(Factorizer32, testSmall) {
  vector<pair<uint32_t, int>> ps;
  const auto& processor = [&ps](uint32_t p, int e) { ps.emplace_back(p, e); };

  factorize32(2, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 1);

  ps.clear();
  factorize32(1024, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 10);

  ps.clear();
  factorize32(10, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, 5);
  EXPECT_EQ(ps[1].second, 1);

  ps.clear();
  factorize32(27, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 3);
  EXPECT_EQ(ps[0].second, 3);

  ps.clear();
  factorize32(840, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 4);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 3);
  EXPECT_EQ(ps[1].first, 3);
  EXPECT_EQ(ps[1].second, 1);
  EXPECT_EQ(ps[2].first, 5);
  EXPECT_EQ(ps[2].second, 1);
  EXPECT_EQ(ps[3].first, 7);
  EXPECT_EQ(ps[3].second, 1);

  ps.clear();
  factorize32(1009, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 1009);
  EXPECT_EQ(ps[0].second, 1);
}

TEST(Factorizer32, testLarge) {
  vector<pair<uint32_t, int>> ps;
  const auto& processor = [&ps](uint32_t p, int e) { ps.emplace_back(p, e); };

  ps.clear();
  factorize32(2 * 1000000007ULL, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, 1000000007);
  EXPECT_EQ(ps[1].second, 1);
}

} // namespace math
