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