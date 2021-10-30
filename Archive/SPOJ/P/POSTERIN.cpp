// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  vector<int> st;
  st.reserve(n);
  int res = 0;
  for (int _ = (0); _ < (n); ++_) {
    int w;
    io::readInt(w);
    io::readInt(w);
    for (; !st.empty() && st.back() > w; st.pop_back()) {
      ++res;
    }
    if (st.empty() || st.back() < w) {
      st.push_back(w);
    }
  }
  io::writeInt(res + static_cast<int>((st).size()));
  io::writeChar('\n');
}
