// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 300000;

int n, vs[MAXN];
int leftSize[MAXN];
vector<int> st;
int64_t res;

inline int64_t process(bool isMax) {
  st.clear();
  int64_t res = 0;
  FOR(i, 0, n) {
    for (; !st.empty() && (isMax ? (vs[st.back()] < vs[i]) : (vs[st.back()] > vs[i]));
         st.pop_back()) {
      int j = st.back();
      res += leftSize[j] * (i - st.back() + 0LL) * vs[j];
    }
    if (st.empty()) {
      leftSize[i] = i + 1;
    } else if (vs[st.back()] != vs[i]) {
      leftSize[i] = i - st.back();
    } else {
      int j = st.back();
      leftSize[i] = leftSize[j] + i - j;
      res += leftSize[j] * (i - j + 0LL) * vs[j];
      st.pop_back();
    }
    st.push_back(i);
  }
  for (; !st.empty(); st.pop_back()) {
    int j = st.back();
    res += leftSize[j] * (n - j + 0LL) * vs[j];
  }
  return res;
}

int main() {
  io::readInt(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  st.reserve(n);
  res = 0;
  io::writeInt(process(true) - process(false));
  io::writeChar('\n');
}
