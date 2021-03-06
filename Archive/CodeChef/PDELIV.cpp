#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define SIZE(vs) static_cast<int>(vs.size())

namespace io {

namespace {

constexpr int kBufferSize = 1 << 15;
char buffer[kBufferSize];
int pos, len;
bool ended = false;

inline void loadBuffer() {
  len = static_cast<int>(fread(buffer, sizeof(char), kBufferSize, stdin));
  pos = 0;
}

inline char nextChar(bool advance = true) {
  if (ended) {
    return 0;
  }
  if (pos >= len) {
    loadBuffer();
    if (len == 0) {
      ended = true;
      return 0;
    }
  }
  return buffer[advance ? pos++ : pos];
}

} // namespace

template<typename T>
void readInt(T& res) {
  for (; isspace(nextChar(false)); nextChar()) {}
  bool negative = nextChar(false) == '-';
  if (negative) {
    nextChar();
  }
  res = 0;
  for (; isdigit(nextChar(false)); res = res * 10 + (nextChar() - '0')) {}
  if (negative) {
    res = -res;
  }
}

} // namespace io

// @autogen
namespace collections {

namespace {

/** floor(num/den) */
template<typename T>
inline T floorDiv(T num, T den) {
  assert(den);
  T res = num / den;
  return (num ^ den) >= 0 ? res : res - static_cast<bool>(num % den);
}

} // namespace

template<typename T>
class MinConvexHullTricksAddDecreasingQueryIncreasing {
private:
  class Line {
  public:
    T a, b, x;

    inline Line(T a_, T b_, T x_) : a(a_), b(b_), x(x_) {}
  };

  vector<Line> lines;
  int head, tail;

  inline void push(T a, T b, T x) {
    lines.emplace_back(a, b, x);
    ++tail;
  }

  inline void pop() {
    lines.pop_back();
    --tail;
  }

public:
  inline void init(int n = -1) {
    lines.clear();
    head = 0;
    tail = 0;
    if (n > 0) {
      lines.reserve(n);
    }
  }

  inline void add(T a, T b) {
    static T inf = numeric_limits<T>::min();
    if (empty()) {
      push(a, b, inf);
      return;
    }
    const auto& lastLine = lines.back();
    if (lastLine.a == a) {
      if (b < lastLine.b) {
        pop();
      } else {
        return;
      }
    }
    T x = inf;
    while (!empty()) {
      const auto& line = lines.back();
      x = floorDiv(b - line.b, line.a - a);
      if (lines.size() == 1 || line.x < x) {
        break;
      }
      pop();
    }
    push(a, b, x);
  }

  inline const Line& queryLine(T x) {
    for (; head + 1 < tail && lines[head + 1].x < x; ++head) {}
    return lines[head];
  }

  inline T query(T x) {
    if (lines.empty()) {
      static T inf = numeric_limits<T>::max();
      return inf;
    }
    const auto& line = queryLine(x);
    return line.a * x + line.b;
  }

  inline bool empty() const {
    return head >= tail;
  }

  inline int size() const {
    return static_cast<int>(lines.size());
  }

  inline typename vector<Line>::iterator begin() {
    return lines.begin() + head;
  }
  inline typename vector<Line>::iterator end() {
    return lines.end();
  }
  inline typename vector<Line>::reverse_iterator rbegin() {
    return lines.rbegin();
  }
  inline typename vector<Line>::reverse_iterator rend() {
    return lines.rend() - head;
  }
};

} // namespace collections

namespace collections {

class IntervalTreeNoUpdateBase {
  inline bool isValid(int nodeIdx) {
    return lowers[nodeIdx] < uppers[nodeIdx];
  }

  int n;

public:
  virtual ~IntervalTreeNoUpdateBase();

  virtual void createNodes(int capacity) = 0;
  virtual void initLeaf(int nodeIdx, int idx) = 0;
  virtual void merge(int idx, int leftIdx, int rightIdx) = 0;

  vector<int> lowers, uppers;

  inline void initLeafsAndRollup(int n_) {
    n = n_;
    int n2 = n << 1;
    lowers.assign(n2, n);
    uppers.assign(n2, -1);
    createNodes(n2);
    for (int i = 0, j = n; i < n; ++i, ++j) {
      lowers[j] = i;
      uppers[j] = i + 1;
      initLeaf(j, i);
    }
    for (int i = n - 1, leftIdx = i << 1, rightIdx = leftIdx | 1; i >= 0;
         --i, leftIdx -= 2, rightIdx -= 2) {
      if (uppers[leftIdx] == lowers[rightIdx]) {
        lowers[i] = lowers[leftIdx];
        uppers[i] = uppers[rightIdx];
        merge(i, leftIdx, rightIdx);
      }
    }
  }

  inline void queryRange(
      int lower, int upper, const function<void(int nodeIdx)>& queryProcessor) {
    for (lower += n, upper += n; lower < upper; lower >>= 1, upper >>= 1) {
      if (lower & 1) {
        if (isValid(lower)) {
          queryProcessor(lower);
        }
        ++lower;
      }
      if ((upper & 1) && isValid(--upper)) {
        queryProcessor(upper);
      }
    }
  }
};

IntervalTreeNoUpdateBase::~IntervalTreeNoUpdateBase() {}

} // namespace collections

int n;
vector<int> xs, ps;

#define I64 int64_t
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define SORTUNIQUE(vs)                                                         \
  sort(vs.begin(), vs.end());                                                  \
  vs.erase(unique(vs.begin(), vs.end()), vs.end())
#define SIZE(vs) static_cast<int>(vs.size())

constexpr int64_t kMaxI64 = numeric_limits<int64_t>::max();

template<typename T>
inline T sqr(T x) {
  return x * x;
}

struct Query {
  int idx, x;
  vector<int> blackouts;

  inline void init(int idx_) {
    idx = idx_;
    int k;
    io::readInt(x);
    io::readInt(k);
    blackouts.reserve(k + 2);
    blackouts.clear();
    blackouts.push_back(-1);
    blackouts.push_back(n);
    FOR(i, 0, k) {
      int blackoutIdx;
      io::readInt(blackoutIdx);
      blackouts.push_back(blackoutIdx - 1);
    }
    SORTUNIQUE(blackouts);
  }

  inline bool operator<(const Query& o) const {
    return x < o.x;
  }
};

vector<Query> queries;

class ChtIntervalTree : public collections::IntervalTreeNoUpdateBase {
public:
  ~ChtIntervalTree() override;
  void createNodes(int capacity) override;
  void initLeaf(int nodeIdx, int idx) override;
  void merge(int idx, int leftIdx, int rightIdx) override;

  vector<collections::MinConvexHullTricksAddDecreasingQueryIncreasing<I64>>
      chts;

  inline I64 query(const Query& query) {
    I64 res = kMaxI64;
    FOR(i, 1, SIZE(query.blackouts)) {
      queryRange(
          query.blackouts[i - 1] + 1,
          query.blackouts[i],
          [this, &res, &query](int nodeIdx) {
            res = min(res, this->chts[nodeIdx].query(query.x));
          });
    }
    return res + sqr<I64>(query.x);
  }
};

ChtIntervalTree::~ChtIntervalTree() {}

void ChtIntervalTree::createNodes(int capacity) {
  chts.resize(capacity);
}

void ChtIntervalTree::initLeaf(int nodeIdx, int idx) {
  auto& cht = chts[nodeIdx];
  cht.init(1);
  I64 x = xs[idx];
  cht.add(-(x << 1), ps[idx] + sqr(x));
}

void ChtIntervalTree::merge(int idx, int leftIdx, int rightIdx) {
  auto& cht = chts[idx];
  auto& left = chts[leftIdx];
  auto& right = chts[rightIdx];
  cht.init(left.size() + right.size());
  auto rightI = right.begin();
  for (auto& leftLine : left) {
    for (; rightI != right.end() && leftLine.a < rightI->a; ++rightI) {
      cht.add(rightI->a, rightI->b);
    }
    cht.add(leftLine.a, leftLine.b);
  }
  for (; rightI != right.end(); ++rightI) {
    cht.add(rightI->a, rightI->b);
  }
}

ChtIntervalTree itree;

#define SORT(vs) sort(vs.begin(), vs.end())

vector<I64> answers;

int main() {
  int m;
  io::readInt(n);
  io::readInt(m);
  xs.resize(n);
  ps.resize(n);
  FOR(i, 0, n) {
    io::readInt(xs[i]);
    io::readInt(ps[i]);
  }
  itree.initLeafsAndRollup(n);
  queries.resize(m);
  FOR(i, 0, m) {
    queries[i].init(i);
  }
  SORT(queries);
  answers.resize(m);
  for (const auto& query : queries) {
    answers[query.idx] = itree.query(query);
  }
  FOR(i, 0, m) {
    printf("%lld\n", answers[i]);
  }
  return 0;
}
