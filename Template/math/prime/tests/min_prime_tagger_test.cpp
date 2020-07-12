#include "gtest/gtest.h"

#include "math/prime/min_prime_tagger.h"

namespace math {

TEST(MinPrimeTagger, test) {
  MinPrimeTagger tagger(20);
  int p, cnt, nxt;

  tagger.process(1, p, cnt, nxt);
  EXPECT_EQ(p, 0);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(2, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(3, p, cnt, nxt);
  EXPECT_EQ(p, 3);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(4, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 2);
  EXPECT_EQ(nxt, 1);

  tagger.process(6, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 3);

  tagger.process(7, p, cnt, nxt);
  EXPECT_EQ(p, 7);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(8, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 3);
  EXPECT_EQ(nxt, 1);

  tagger.process(9, p, cnt, nxt);
  EXPECT_EQ(p, 3);
  EXPECT_EQ(cnt, 2);
  EXPECT_EQ(nxt, 1);

  tagger.process(10, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 5);

  tagger.process(11, p, cnt, nxt);
  EXPECT_EQ(p, 11);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(12, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 2);
  EXPECT_EQ(nxt, 3);

  tagger.process(13, p, cnt, nxt);
  EXPECT_EQ(p, 13);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(14, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 7);

  tagger.process(16, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 4);
  EXPECT_EQ(nxt, 1);

  tagger.process(17, p, cnt, nxt);
  EXPECT_EQ(p, 17);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);

  tagger.process(18, p, cnt, nxt);
  EXPECT_EQ(p, 2);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 9);

  tagger.process(19, p, cnt, nxt);
  EXPECT_EQ(p, 19);
  EXPECT_EQ(cnt, 1);
  EXPECT_EQ(nxt, 1);
}

} // namespace math
