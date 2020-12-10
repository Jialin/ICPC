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
#include "math/bit/submasks.h"

const string ATOMS[100] = {
    "H",  "He", "Li", "Be", "B",  "C",  "N",  "O",  "F",  "Ne", "Na", "Mg",
    "Al", "Si", "P",  "S",  "Cl", "Ar", "K",  "Ca", "Sc", "Ti", "V",  "Cr",
    "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y",  "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd",
    "In", "Sn", "Sb", "Te", "I",  "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
    "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf",
    "Ta", "W",  "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po",
    "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U",  "Np", "Pu", "Am", "Cm",
    "Bk", "Cf", "Es", "Fm"};
const int MAXN = 17;
const int MAXMASK = 1 << MAXN;

unordered_map<string, int> atomIds;
int n, m;
int atoms[MAXN], comps[MAXN], compSum[MAXN + 1];
int maskSum[MAXMASK], from[MAXMASK];
bool visited[MAXMASK];
char s[10];

inline bool calc(int mask, int compIdx) {
  if (!mask) {
    return true;
  }
  if (visited[mask]) {
    return from[mask] >= 0;
  }
  visited[mask] = true;
  for (int remMask = mask; remMask > 0;) {
    int bit = __builtin_ctz(remMask);
    if (maskSum[mask ^ (1 << bit)] == compSum[compIdx]) {
      if (calc(mask ^ (1 << bit), compIdx - 1)) {
        from[mask] = bit;
        return true;
      }
    } else if (maskSum[mask ^ (1 << bit)] > compSum[compIdx]) {
      if (calc(mask ^ (1 << bit), compIdx)) {
        from[mask] = bit;
        return true;
      }
    }
    remMask ^= 1 << bit;
  }
  return false;
}

int main() {
  int atomId = 0;
  for (auto& atom : ATOMS) {
    atomIds[atom] = ++atomId;
  }
  while (scanf("%d%d", &n, &m) != EOF && (n || m)) {
    int atomSum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      assert(atomIds.count(s));
      atoms[i] = atomIds[s];
      atomSum += atoms[i];
    }
    compSum[0] = 0;
    for (int i = 0; i < m; ++i) {
      scanf("%s", s);
      assert(atomIds.count(s));
      comps[i] = atomIds[s];
      compSum[i + 1] = compSum[i] + comps[i];
    }
    if (atomSum != compSum[m]) {
      puts("NO");
      continue;
    }
    maskSum[0] = 0;
    for (int mask = 1; mask < 1 << n; ++mask) {
      int bit = __builtin_ctz(mask);
      maskSum[mask] = maskSum[mask ^ (1 << bit)] + atoms[bit];
    }
    memset(from, 0xFF, sizeof(int) << n);
    memset(visited, 0, sizeof(bool) << n);
    if (!calc((1 << n) - 1, m - 1)) {
      puts("NO");
      continue;
    }
    puts("YES");
    bool first = true;
    for (int mask = (1 << n) - 1, compIdx = m - 1; mask > 0;) {
      int bit = from[mask];
      if (!first) {
        putchar('+');
      }
      first = false;
      printf("%s", ATOMS[atoms[bit] - 1].c_str());
      mask ^= 1 << bit;
      if (maskSum[mask] == compSum[compIdx]) {
        printf("->%s\n", ATOMS[comps[compIdx] - 1].c_str());
        --compIdx;
        first = true;
      }
    }
  }
}