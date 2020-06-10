#include "gtest/gtest.h"

#include "math/prime/mark_primes.h"

namespace math {

TEST(MarkPrimes, test) {
  vector<bool> isPrimes;
  markPrimes(20, isPrimes);
  ASSERT_EQ(isPrimes.size(), 21);
  EXPECT_EQ(isPrimes[0], false);
  EXPECT_EQ(isPrimes[1], false);
  EXPECT_EQ(isPrimes[2], true);
  EXPECT_EQ(isPrimes[3], true);
  EXPECT_EQ(isPrimes[4], false);
  EXPECT_EQ(isPrimes[5], true);
  EXPECT_EQ(isPrimes[6], false);
  EXPECT_EQ(isPrimes[7], true);
  EXPECT_EQ(isPrimes[8], false);
  EXPECT_EQ(isPrimes[9], false);
  EXPECT_EQ(isPrimes[10], false);
  EXPECT_EQ(isPrimes[11], true);
  EXPECT_EQ(isPrimes[12], false);
  EXPECT_EQ(isPrimes[13], true);
  EXPECT_EQ(isPrimes[14], false);
  EXPECT_EQ(isPrimes[15], false);
  EXPECT_EQ(isPrimes[16], false);
  EXPECT_EQ(isPrimes[17], true);
  EXPECT_EQ(isPrimes[18], false);
  EXPECT_EQ(isPrimes[19], true);
  EXPECT_EQ(isPrimes[20], false);
}

} // namespace math
