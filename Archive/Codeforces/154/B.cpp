#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#include "collections/forward_star/forward_star_stack.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/prime/factorizer.h"

const int MAXN = 100000 + 1;
const int MAXM = 100000 * 6;

bool status[MAXN];
math::Factorizer fact(MAXN);
collections::ForwardStarStacks<> fss(MAXN, MAXM);
int conflictIdx, idx;

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  const auto& checkProcessor = [](int prime, int) {
    for (; !fss.empty(prime); fss.pop(prime)) {
      int v = fss.top(prime);
      if (status[v]) {
        conflictIdx = v;
        return false;
      }
    }
    return true;
  };
  const auto& addProcessor = [](int prime, int) {
    fss.push(prime, idx);
    return true;
  };

  for (int opIdx = 0; opIdx < m; ++opIdx) {
    char op[2];
    io::readCharArray(op);
    io::readInt(idx);
    if (op[0] == '+') {
      if (status[idx]) {
        io::writeCharArray("Already on\n");
        continue;
      }
      conflictIdx = -1;
      fact.factorize(idx, checkProcessor);
      if (conflictIdx < 0) {
        status[idx] = true;
        fact.factorize(idx, addProcessor);
        io::writeCharArray("Success\n");
      } else {
        io::writeCharArray("Conflict with ");
        io::writeInt(conflictIdx);
        io::writeChar('\n');
      }
    } else {
      if (!status[idx]) {
        io::writeCharArray("Already off\n");
      } else {
        io::writeCharArray("Success\n");
        status[idx] = false;
      }
    }
  }
}
