#include "gtest/gtest.h"

#define MANACHER_ALL
#include "string/palindrome/manacher_macros.h"

#include "string/palindrome/manacher.h"

namespace str {

TEST(ManacherTest, basic) {
  Manacher man;

  man.calc("aybabtu");
  ASSERT_EQ(15, man.rs.size());

  EXPECT_EQ(0, man.oddLower(0));
  EXPECT_EQ(1, man.oddUpper(0));
  EXPECT_EQ(1, man.oddSize(0));
  EXPECT_EQ(1, man.oddLower(1));
  EXPECT_EQ(2, man.oddUpper(1));
  EXPECT_EQ(1, man.oddSize(1));
  EXPECT_EQ(2, man.oddLower(2));
  EXPECT_EQ(3, man.oddUpper(2));
  EXPECT_EQ(1, man.oddSize(2));
  EXPECT_EQ(2, man.oddLower(3));
  EXPECT_EQ(5, man.oddUpper(3));
  EXPECT_EQ(3, man.oddSize(3));
  EXPECT_EQ(4, man.oddLower(4));
  EXPECT_EQ(5, man.oddUpper(4));
  EXPECT_EQ(1, man.oddSize(4));
  EXPECT_EQ(5, man.oddLower(5));
  EXPECT_EQ(6, man.oddUpper(5));
  EXPECT_EQ(1, man.oddSize(5));
  EXPECT_EQ(6, man.oddLower(6));
  EXPECT_EQ(7, man.oddUpper(6));
  EXPECT_EQ(1, man.oddSize(6));

  EXPECT_EQ(0, man.evenLower(0));
  EXPECT_EQ(0, man.evenUpper(0));
  EXPECT_EQ(0, man.evenSize(0));
  EXPECT_EQ(1, man.evenLower(1));
  EXPECT_EQ(1, man.evenUpper(1));
  EXPECT_EQ(0, man.evenSize(1));
  EXPECT_EQ(2, man.evenLower(2));
  EXPECT_EQ(2, man.evenUpper(2));
  EXPECT_EQ(0, man.evenSize(2));
  EXPECT_EQ(3, man.evenLower(3));
  EXPECT_EQ(3, man.evenUpper(3));
  EXPECT_EQ(0, man.evenSize(3));
  EXPECT_EQ(4, man.evenLower(4));
  EXPECT_EQ(4, man.evenUpper(4));
  EXPECT_EQ(0, man.evenSize(4));
  EXPECT_EQ(5, man.evenLower(5));
  EXPECT_EQ(5, man.evenUpper(5));
  EXPECT_EQ(0, man.evenSize(5));
  EXPECT_EQ(6, man.evenLower(6));
  EXPECT_EQ(6, man.evenUpper(6));
  EXPECT_EQ(0, man.evenSize(6));
  EXPECT_EQ(make_pair(2, 5), man.longestPalindrome());

  man.calc("cabba");
  ASSERT_EQ(11, man.rs.size());

  EXPECT_EQ(0, man.oddLower(0));
  EXPECT_EQ(1, man.oddUpper(0));
  EXPECT_EQ(1, man.oddSize(0));
  EXPECT_EQ(1, man.oddLower(1));
  EXPECT_EQ(2, man.oddUpper(1));
  EXPECT_EQ(1, man.oddSize(1));
  EXPECT_EQ(2, man.oddLower(2));
  EXPECT_EQ(3, man.oddUpper(2));
  EXPECT_EQ(1, man.oddSize(2));
  EXPECT_EQ(3, man.oddLower(3));
  EXPECT_EQ(4, man.oddUpper(3));
  EXPECT_EQ(1, man.oddSize(3));
  EXPECT_EQ(4, man.oddLower(4));
  EXPECT_EQ(5, man.oddUpper(4));
  EXPECT_EQ(1, man.oddSize(4));

  EXPECT_EQ(0, man.evenLower(0));
  EXPECT_EQ(0, man.evenUpper(0));
  EXPECT_EQ(0, man.evenSize(0));
  EXPECT_EQ(1, man.evenLower(1));
  EXPECT_EQ(1, man.evenUpper(1));
  EXPECT_EQ(0, man.evenSize(1));
  EXPECT_EQ(2, man.evenLower(2));
  EXPECT_EQ(2, man.evenUpper(2));
  EXPECT_EQ(0, man.evenSize(2));
  EXPECT_EQ(1, man.evenLower(3));
  EXPECT_EQ(5, man.evenUpper(3));
  EXPECT_EQ(4, man.evenSize(3));
  EXPECT_EQ(4, man.evenLower(4));
  EXPECT_EQ(4, man.evenUpper(4));
  EXPECT_EQ(0, man.evenSize(4));
  EXPECT_EQ(make_pair(1, 5), man.longestPalindrome());

  man.calc("cabbaccc");
  ASSERT_EQ(17, man.rs.size());

  EXPECT_EQ(0, man.oddLower(0));
  EXPECT_EQ(1, man.oddUpper(0));
  EXPECT_EQ(1, man.oddSize(0));
  EXPECT_EQ(1, man.oddLower(1));
  EXPECT_EQ(2, man.oddUpper(1));
  EXPECT_EQ(1, man.oddSize(1));
  EXPECT_EQ(2, man.oddLower(2));
  EXPECT_EQ(3, man.oddUpper(2));
  EXPECT_EQ(1, man.oddSize(2));
  EXPECT_EQ(3, man.oddLower(3));
  EXPECT_EQ(4, man.oddUpper(3));
  EXPECT_EQ(1, man.oddSize(3));
  EXPECT_EQ(4, man.oddLower(4));
  EXPECT_EQ(5, man.oddUpper(4));
  EXPECT_EQ(1, man.oddSize(4));
  EXPECT_EQ(5, man.oddLower(5));
  EXPECT_EQ(6, man.oddUpper(5));
  EXPECT_EQ(1, man.oddSize(5));
  EXPECT_EQ(5, man.oddLower(6));
  EXPECT_EQ(8, man.oddUpper(6));
  EXPECT_EQ(3, man.oddSize(6));
  EXPECT_EQ(7, man.oddLower(7));
  EXPECT_EQ(8, man.oddUpper(7));
  EXPECT_EQ(1, man.oddSize(7));

  EXPECT_EQ(0, man.evenLower(0));
  EXPECT_EQ(0, man.evenUpper(0));
  EXPECT_EQ(0, man.evenSize(0));
  EXPECT_EQ(1, man.evenLower(1));
  EXPECT_EQ(1, man.evenUpper(1));
  EXPECT_EQ(0, man.evenSize(1));
  EXPECT_EQ(2, man.evenLower(2));
  EXPECT_EQ(2, man.evenUpper(2));
  EXPECT_EQ(0, man.evenSize(2));
  EXPECT_EQ(0, man.evenLower(3));
  EXPECT_EQ(6, man.evenUpper(3));
  EXPECT_EQ(6, man.evenSize(3));
  EXPECT_EQ(4, man.evenLower(4));
  EXPECT_EQ(4, man.evenUpper(4));
  EXPECT_EQ(0, man.evenSize(4));
  EXPECT_EQ(5, man.evenLower(5));
  EXPECT_EQ(5, man.evenUpper(5));
  EXPECT_EQ(0, man.evenSize(5));
  EXPECT_EQ(5, man.evenLower(6));
  EXPECT_EQ(7, man.evenUpper(6));
  EXPECT_EQ(2, man.evenSize(6));
  EXPECT_EQ(6, man.evenLower(7));
  EXPECT_EQ(8, man.evenUpper(7));
  EXPECT_EQ(2, man.evenSize(7));

  EXPECT_EQ(make_pair(0, 6), man.longestPalindrome());
}

} // namespace str
