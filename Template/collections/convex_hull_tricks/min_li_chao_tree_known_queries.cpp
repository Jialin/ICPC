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
class MinLiChaoTreeKnownQueries {
private:
  class Node {
  public:
    T a, b;
    int leftIdx, rightIdx;

    inline Node(T a_, T b_, int leftIdx_ = -1, int rightIdx_ = -1)
        : a(a_), b(b_), leftIdx(leftIdx_), rightIdx(rightIdx_) {}
  };

  inline int newNode(T a, T b) {
    int size = static_cast<int>(nodes.size());
    nodes.emplace_back(a, b);
    return size;
  }

  int n;
  vector<T> queries;
  vector<Node> nodes;

public:
  inline void init(const vector<T>& orderedUniqueQueries) {
    this->queries = orderedUniqueQueries;
    n = static_cast<int>(orderedUniqueQueries.size());
    int capacity = 1 << (31 - __builtin_clz(n));
    nodes.reserve(capacity << (1 + (capacity < n)));
    reset();
  }

  inline void reset() {
    nodes.clear();
  }

  inline void add(T a, T b) {
    if (nodes.empty()) {
      newNode(a, b);
      return;
    }
    int idx = 0, lower = 0, upper = n;
    while (true) {
      auto& node = nodes[idx];
      if (node.a == a) {
        if (node.b > b) {
          node.b = b;
        }
        break;
      }
      T joint = floorDiv(node.b - b, a - node.a);
      if (joint < queries[lower]) {
        if (node.a > a) {
          node.a = a;
          node.b = b;
        }
        break;
      }
      if (joint >= queries[upper - 1]) {
        if (a > node.a) {
          node.a = a;
          node.b = b;
        }
        break;
      }
      if (lower + 1 >= upper) {
        break;
      }
      int medium = (lower + upper) >> 1;
      if ((joint < queries[medium]) ^ (a > node.a)) {
        swap(node.a, a);
        swap(node.b, b);
      }
      if (joint < queries[medium]) {
        idx = node.leftIdx;
        if (idx < 0) {
          node.leftIdx = newNode(a, b);
          break;
        }
        upper = medium;
      } else {
        idx = node.rightIdx;
        if (idx < 0) {
          node.rightIdx = newNode(a, b);
          break;
        }
        lower = medium;
      }
    }
  }

  inline T query(T x) const {
    assert(!nodes.empty());
    int idx = static_cast<int>(lower_bound(queries.begin(), queries.end(), x) -
                               queries.begin());
    assert(idx < static_cast<int>(queries.size()) && queries[idx] == x);
    return queryIdx(idx);
  }

  inline T queryIdx(int queryIdx) const {
    assert(!nodes.empty());
    T x = queries[queryIdx];
    T res = nodes[0].a * x + nodes[0].b;
    for (int idx = 0, lower = 0, upper = n; idx >= 0;) {
      const auto& node = nodes[idx];
      if (idx) {
        T subRes = node.a * x + node.b;
        if (res > subRes) {
          res = subRes;
        }
      }
      int medium = (lower + upper) >> 1;
      if (medium <= queryIdx) {
        idx = node.rightIdx;
        lower = medium;
      } else {
        idx = node.leftIdx;
        upper = medium;
      }
    }
    return res;
  }
};

} // namespace collections