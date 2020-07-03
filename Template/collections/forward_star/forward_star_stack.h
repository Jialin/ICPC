#include <vector>

using namespace std;

namespace collections {

template<typename V = int>
class ForwardStarStacks {
public:
  inline ForwardStarStacks(int n, int maxAddCnt = -1) {
    init(n, maxAddCnt);
  }

  inline void init(int n, int maxAddCnt = -1) {
    lastOut_.assign(n, -1);
    if (maxAddCnt >= 0) {
      nxtOut_.reserve(maxAddCnt);
      vs_.reserve(maxAddCnt);
    }
    nxtOut_.clear();
    vs_.clear();
  }

  inline void push(int x, V v) {
    int edgeIdx = static_cast<int>(vs_.size());
    nxtOut_.push_back(lastOut_[x]);
    vs_.push_back(std::move(v));
    lastOut_[x] = edgeIdx;
  }

  inline void pop(int x) {
    lastOut_[x] = nxtOut_[lastOut_[x]];
  }

  inline bool empty(int x) const {
    return lastOut_[x] < 0;
  }

  inline const V& top(int x) const {
    return vs_[lastOut_[x]];
  }

private:
  vector<int> lastOut_, nxtOut_;
  vector<V> vs_;
};

} // namespace collections
