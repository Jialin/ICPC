namespace cs {

template<typename V>
class IntervalTreeWithLazyPropagation {
  int n2;
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
    V& l = vs[left(idx)];
    V& r = vs[right(idx)];
    v.pushLabelTo(l);
    v.pushLabelTo(r);
    v.clearLabel();
    v.merge(l, r);
  }

  inline void pushLabelInRange(int lower, int upper) {
    lower = (lower + n) >> 1;
    upper = (upper - 1 + n) >> 1;
    for (idxToUpdate.clear(); lower < upper; lower >>= 1, upper >>= 1) {
      if (vs[lower].isValid()) idxToUpdate.push_back(lower);
      if (vs[upper].isValid()) idxToUpdate.push_back(upper);
    }
    for ( ; lower > 0 && vs[lower].isValid(); lower >>= 1) idxToUpdate.push_back(lower);
    for (int i = static_cast<int>(idxToUpdate.size()) - 1; i >= 0; --i) pushLabel(idxToUpdate[i]);
  }

  inline void merge(int idx) {
    vs[idx].merge(vs[left(idx)], vs[right(idx)]);
  }

public:
  int n;
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
    if (lower >= upper) return;
    pushLabelInRange(lower, upper);
    bool mergeL = false;
    bool mergeR = false;
    for (lower += n, upper += n; lower < upper; lower >>= 1, upper >>= 1) {
      if (mergeL) merge(lower - 1);
      if (mergeR) merge(upper);
      if (lower & 1) {
        update.pushLabelTo(vs[lower++]);
        mergeL = true;
      }
      if (upper & 1) {
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
}; // class IntervalTreeWithLazyPropagation
} // namespace cs

namespace testing {

template<typename V>
string toDisplay(cs::IntervalTreeWithLazyPropagation<V> itree) {
  ostringstream ss;
  for (int i = 1; i < itree.n << 1; ++i) {
    auto& v = itree.vs[i];
    if (!v.isValid()) continue;
    ss << "[" << v.lower << "," << v.upper << "): " << v.toDisplay() << endl;
  }
  return ss.str();
}
} // namespace testing

/***********************************************************************************************************************
 * Example LabelValue: SPOJ SEGSQRSS
 **********************************************************************************************************************/
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

/***********************************************************************************************************************
 * Example LabelValue: SPOJ QUERYIT
 **********************************************************************************************************************/
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
  int cnt0_, cnt1_;
  int incRes_, decRes_;
  bool flip;

  inline int cnt0() const {
    return flip ? cnt1_ : cnt0_;
  }

  inline int cnt1() const {
    return flip ? cnt0_ : cnt1_;
  }

  inline int incRes() const {
    return flip ? decRes_ : incRes_;
  }

  inline int decRes() const {
    return flip ? incRes_ : decRes_;
  }

  inline void clearLabel() {
    flip = false;
  }

  inline void operator = (const LabeledValue& o) {
    cnt0_ = o.cnt0();
    cnt1_ = o.cnt1();
    incRes_ = o.incRes();
    decRes_ = o.decRes();
    clearLabel();
  }

  inline void initLeaf(int idx) {
    char c = s[idx];
    cnt0_ = c == '0';
    cnt1_ = c == '1';
    incRes_ = 1;
    decRes_ = 1;
    clearLabel();
  }

  inline void clear() {
    cnt0_ = 0;
    cnt1_ = 0;
    incRes_ = 0;
    decRes_ = 0;
    clearLabel();
  }

  inline void pushLabelTo(LabeledValue &o) const {
    if (flip) o.flip = !o.flip;
  }

  inline void merge(const LabeledValue& l, const LabeledValue& r) {
    cnt0_ = l.cnt0() + r.cnt0();
    cnt1_ = l.cnt1() + r.cnt1();
    incRes_ = max(l.incRes() + r.cnt1(), l.cnt0() + r.incRes());
    decRes_ = max(l.decRes() + r.cnt0(), l.cnt1() + r.decRes());
    clearLabel();
  }

  inline string toDisplay() const {
    ostringstream ss;
    if (flip) ss << "flipped";
    ss << endl;
    ss << "\tcnt:" << cnt0() << "," << cnt1() << endl;
    ss << "\tincRes:" << incRes() << endl;
    ss << "\tdecRes:" << decRes();
    return ss.str();
  }
};
