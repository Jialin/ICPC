#include "gtest/gtest.h"

#include "math/prime/min_prime_tagger.h"

namespace math {

TEST(MinPrimeTagger, test) {
  MinPrimeTagger tagger(20);
  EXPECT_EQ(tagger.getMinPrimeFactor(0), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(1), 1);
  EXPECT_EQ(tagger.getMinPrimeFactor(2), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(3), 3);
  EXPECT_EQ(tagger.getMinPrimeFactor(4), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(5), 5);
  EXPECT_EQ(tagger.getMinPrimeFactor(6), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(7), 7);
  EXPECT_EQ(tagger.getMinPrimeFactor(8), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(9), 3);
  EXPECT_EQ(tagger.getMinPrimeFactor(10), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(11), 11);
  EXPECT_EQ(tagger.getMinPrimeFactor(12), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(13), 13);
  EXPECT_EQ(tagger.getMinPrimeFactor(14), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(15), 3);
  EXPECT_EQ(tagger.getMinPrimeFactor(16), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(17), 17);
  EXPECT_EQ(tagger.getMinPrimeFactor(18), 2);
  EXPECT_EQ(tagger.getMinPrimeFactor(19), 19);
  EXPECT_EQ(tagger.getMinPrimeFactor(20), 2);
}

} // namespace math
