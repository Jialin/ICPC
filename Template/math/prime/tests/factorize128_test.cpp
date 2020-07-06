#include "gtest/gtest.h"

#include "math/prime/factorize128.h"

namespace math {

TEST(Factorizer, testSmall) {
  MontgomeryMul mont;
  vector<pair<__uint128_t, __uint128_t>> ps;
  const auto& processor = [&ps](__uint128_t p, int e) {
    ps.emplace_back(p, e);
    return true;
  };

  factorize128(2, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 1);

  ps.clear();
  factorize128(1024, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 10);

  ps.clear();
  factorize128(10, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, 5);
  EXPECT_EQ(ps[1].second, 1);

  ps.clear();
  factorize128(27, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 3);
  EXPECT_EQ(ps[0].second, 3);

  ps.clear();
  factorize128(840, processor);
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
  factorize128(1009, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 1009);
  EXPECT_EQ(ps[0].second, 1);
}

TEST(Factorizer, testLarge) {
  MontgomeryMul mont;
  vector<pair<__uint128_t, __uint128_t>> ps;
  const auto& processor = [&ps](__uint128_t p, int e) {
    ps.emplace_back(p, e);
    return true;
  };

  ps.clear();
  factorize128(2000000014ULL, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 2);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, 1000000007);
  EXPECT_EQ(ps[1].second, 1);

  ps.clear();
  factorize128(1000000014000000049ULL, processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(ps[0].first, 1000000007);
  EXPECT_EQ(ps[0].second, 2);

  ps.clear();
  factorize128(
      __uint128_t(9616562014629204ULL) * 100000000000000ULL + 97194293996611ULL,
      processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 973825889);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, __uint128_t(98750322036562790) * 10000 + 2499);
  EXPECT_EQ(ps[1].second, 1);

  ps.clear();
  factorize128(
      __uint128_t(9553427693635611ULL) * 100000000000000ULL + 1863533963531ULL,
      processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 973806882626147ULL);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, 981039245468473ULL);
  EXPECT_EQ(ps[1].second, 1);

  ps.clear();
  factorize128(
      __uint128_t(9637823792045106ULL) * 100000000000000ULL + 91122291047909ULL,
      processor);
  sort(ps.begin(), ps.end());
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(ps[0].first, 244564652505673ULL);
  EXPECT_EQ(ps[0].second, 1);
  EXPECT_EQ(ps[1].first, 3940808163935933ULL);
  EXPECT_EQ(ps[1].second, 1);
}

} // namespace math
