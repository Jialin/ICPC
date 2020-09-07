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

#include "debug/debug.h"
#include "io/read_int.h"

int n, k;
vector<int> primes;
vector<bool> tag;

int main() {
  io::readInt(n);
  io::readInt(k);
  primes.reserve(16);
  for (int prime = 2; prime <= k / prime; ++prime) {
    if (k % prime) {
      continue;
    }
    primes.push_back(prime);
    for (k /= prime; !(k % prime); k /= prime, primes.back() *= prime) {}
  }
  if (k > 1) {
    primes.push_back(k);
  }
  tag.assign(primes.size(), false);
  for (int i = 0; i < n; ++i) {
    int v;
    io::readInt(v);
    for (int j = static_cast<int>(tag.size()) - 1; j >= 0; --j) {
      if (tag[j]) {
        continue;
      }
      if (!(v % primes[j])) {
        tag[j] = true;
      }
    }
  }
  bool res = true;
  for (size_t i = 0; i < primes.size(); ++i) {
    if (!tag[i]) {
      res = false;
      break;
    }
  }
  puts(res ? "Yes" : "No");
  return 0;
}
