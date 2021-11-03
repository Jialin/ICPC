// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

int n;
vector<int> st;

inline int calc() {
  st.clear();
  int res = 0;
  FOR(_, 0, n) {
    int h;
    io::readInt(h);
    for (; !st.empty() && st.back() > h; st.pop_back()) {}
    if (h && (st.empty() || st.back() != h)) {
      st.push_back(h);
      ++res;
    }
  }
  return res;
}

int main() {
  st.reserve(MAXN);
  int taskIdx = 1;
  while (io::readInt(n)) {
    io::writeCharArray("Case ");
    io::writeInt(taskIdx++);
    io::writeChar(':');
    io::writeChar(' ');
    io::writeInt(calc());
    io::writeChar('\n');
  }
  return 0;
}
