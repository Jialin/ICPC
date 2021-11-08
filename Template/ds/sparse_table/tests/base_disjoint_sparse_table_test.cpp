#include "gtest/gtest.h"

#define BASE_DISJOINT_SPARSE_TABLE_CALC
#include "ds/sparse_table/base_disjoint_sparse_table_macros.h"

#include "ds/sparse_table/base_disjoint_sparse_table.h"
#include "math/mod/mul.h"

namespace ds {

struct ProductModDisjointSparseTable : BaseDisjointSparseTable<int, 4, 6> {
  inline void combine(const int& leftValue, const int& rightValue, int& res) const override {
    res = math::mulMod(leftValue, rightValue, 1000000);
  }
};

TEST(BaseDisjointSparseTableTest, basic) {
  ProductModDisjointSparseTable st;
  st.init({1, 2, 3, 4, 5, 6});

  EXPECT_EQ(1, st.calc(0, 1));
  EXPECT_EQ(2, st.calc(0, 2));
  EXPECT_EQ(6, st.calc(0, 3));
  EXPECT_EQ(24, st.calc(0, 4));
  EXPECT_EQ(120, st.calc(0, 5));
  EXPECT_EQ(720, st.calc(0, 6));

  EXPECT_EQ(2, st.calc(1, 2));
  EXPECT_EQ(6, st.calc(1, 3));
  EXPECT_EQ(24, st.calc(1, 4));
  EXPECT_EQ(120, st.calc(1, 5));
  EXPECT_EQ(720, st.calc(1, 6));

  EXPECT_EQ(3, st.calc(2, 3));
  EXPECT_EQ(12, st.calc(2, 4));
  EXPECT_EQ(60, st.calc(2, 5));
  EXPECT_EQ(360, st.calc(2, 6));

  EXPECT_EQ(4, st.calc(3, 4));
  EXPECT_EQ(20, st.calc(3, 5));
  EXPECT_EQ(120, st.calc(3, 6));

  EXPECT_EQ(5, st.calc(4, 5));
  EXPECT_EQ(30, st.calc(4, 6));

  EXPECT_EQ(6, st.calc(5, 6));
}

} // namespace ds
