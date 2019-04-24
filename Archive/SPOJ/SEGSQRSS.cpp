#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace cs {

template<typename V>
class IntervalTreeWithPropagation {
  vector<int> idxToUpdate;
  vector<int> idxToUpdateOther;

  inline int left(int idx) {
    return idx << 1;
  }

  inline int right(int idx) {
    return left(idx) | 1;
  }

  inline void pushLabel(int idx) {
    V& v = vs[idx];
    v.pushLabelTo(vs[left(idx)]);
    v.pushLabelTo(vs[right(idx)]);
    v.clearLabel();
  }

  inline void pushLabelInRange(int lower, int upper) {
    lower = (lower + n) >> 1;
    upper = (upper - 1 + n) >> 1;
    for (idxToUpdate.clear(); lower < upper; lower >>= 1, upper >>= 1) {
      if (vs[lower].isValid()) idxToUpdate.push_back(lower);
      if (vs[upper].isValid()) idxToUpdate.push_back(upper);
    }
    for ( ; lower > 0 && vs[lower].isValid(); lower >>= 1) idxToUpdate.push_back(lower);
    for (int idx = static_cast<int>(idxToUpdate.size()) - 1; idx >= 0; --idx) pushLabel(idx);
  }

  inline void merge(int idx) {
    vs[idx].merge(vs[left(idx)], vs[right(idx)]);
  }

public:
  int n, n2;
  vector<V> vs;

  inline void init(int _n) {
    n = _n;
    n2 = n << 1;
    vs.resize(n2 + 2);
    for (int i = 0, j = n; i < n; ++i, ++j) {
      V& v = vs[j];
      v.lower = i;
      v.upper = i + 1;
      v.initLeaf(i);
      v.clearLabel();
      vs[i].clearLabel();
    }
    for (int i = n - 1; i >= 0; --i) {
      const V& l = vs[left(i)];
      const V& r = vs[right(i)];
      V& v = vs[i];
      if (l.upper == r.lower) {
        v.lower = l.lower;
        v.upper = r.upper;
        v.merge(l, r);
      } else {
        // Invalid node
        v.lower = n;
        v.upper = -1;
      }
    }
  }

  inline void updateRange(int lower, int upper, const V& update) {
    pushLabelInRange(lower, upper);
    bool mergeL = false;
    bool mergeR = false;
    for (lower += n, upper += n; lower < upper; lower >>= 1, upper >>= 1) {
      if (mergeL) merge(lower - 1);
      if (mergeR) merge(upper);
      if ((lower & 1) > 0) {
        update.pushLabelTo(vs[lower++]);
        mergeL = true;
      }
      if ((upper & 1) > 0) {
        update.pushLabelTo(vs[--upper]);
        mergeR = true;
      }
    }
    for (--lower; upper > 0; lower >>= 1, upper >>= 1) {
      if (mergeL) merge(lower);
      if (mergeR && (!mergeL || lower != upper)) merge(upper);
    }
  }

  inline V& calcRange(int lower, int upper) {
    if (lower >= upper) {
      vs[n2].clear();
      return vs[n2];
    }
    pushLabelInRange(lower, upper);
    idxToUpdate.clear();
    idxToUpdateOther.clear();
    for (lower += n, upper += n; lower < upper; lower >>= 1, upper >>= 1) {
      if (lower & 1) {
        if (vs[lower].isValid()) idxToUpdate.push_back(lower);
        ++lower;
      }
      if ((upper & 1) && vs[--upper].isValid()) idxToUpdateOther.push_back(upper);
    }
    reverse(idxToUpdateOther.begin(), idxToUpdateOther.end());
    for (int idx : idxToUpdateOther) idxToUpdate.push_back(idx);
    int resIdx = n2;
    bool first = true;
    for (int idx : idxToUpdate) {
      if (first) {
        first = false;
        vs[resIdx] = vs[idx];
        continue;
      }
      vs[resIdx ^ 1].lower = vs[resIdx].lower;
      vs[resIdx ^ 1].upper = vs[idx].upper;
      vs[resIdx ^ 1].merge(vs[resIdx], vs[idx]);
      resIdx ^= 1;
    }
    return vs[resIdx];
  }
};
} // namespace cs

const int MAXN = 100000;

int v[MAXN];

class LabeledValue {
public:
  int lower, upper;

  inline bool isValid() const {
    return lower < upper;
  }

  inline int size() const {
    return upper - lower;
  }

  /** Includes all values and labels. */
  long long sum, sum2;
  int op;
  long long update;

  inline long long getSum() const {
    if (op == 1) {
      return sum + update * size();
    } else if (op == 2) {
      return update * size();
    } else {
      return sum;
    }
  }

  inline long long getSum2() const {
    if (op == 1) {
      return sum2 + sum * update + update * update * size();
    } else if (op == 2) {
      return update * update * size();
    } else {
      return sum2;
    }
  }

  inline void clearLabel() {
    op = 0;
  }

  inline void operator = (const LabeledValue& o) {
    sum = o.getSum();
    sum2 = o.getSum2();
    clearLabel();
  }

  inline void initLeaf(int idx) {
    sum = v[idx];
    sum2 = sum * sum;
    clearLabel();
  }

  inline void clear() {
    sum = 0;
    sum2 = 0;
    clearLabel();
  }

  inline void pushLabelTo(LabeledValue &o) const {
    if (!op) return;
    if (!o.op) {
      o.op = op;
      o.update = update;
      return;
    }
    if (op == 1) {
      o.update += update;
    } else {
      o.op = 2;
      o.update = update;
    }
  }

  inline void merge(const LabeledValue& l, const LabeledValue& r) {
    sum = l.getSum() + r.getSum();
    sum2 = l.getSum2() + r.getSum2();
    clearLabel();
  }
};

cs::IntervalTreeWithPropagation<LabeledValue> itree;
LabeledValue label;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n, Q; scanf("%d%d", &n, &Q);
    FOR(i, 0, n) scanf("%d", v + i);
    itree.init(n);
    printf("Case %d:\n", taskIdx);
    FOR(_, 0, Q) {
      int op, fromIdx, toIdx; scanf("%d%d%d", &op, &fromIdx, &toIdx); --fromIdx;
      if (op == 2) {
        auto& res = itree.calcRange(fromIdx, toIdx);
        printf("%lld\n", res.getSum2());
      } else {
        label.op = 2 - op;
        scanf("%lld", &label.update);
        itree.updateRange(fromIdx, toIdx, label);
      }
    }
  }
  return 0;
}
