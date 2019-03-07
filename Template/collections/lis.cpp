namespace cs { namespace lis {

template<typename T>
class LongestIncreasingSubsequence {
  vector<T> lis;

public:
  // Length of lis
  int length;

  // Initializes
  inline void init(int n) {
    lis.resize(n);
    length = 0;
  }

  // Try to add v to lis
  inline void add(const T& v) {
    T absv = abs(v);
    const auto& lisBegin = lis.begin();
    long idx = lower_bound(lisBegin, lisBegin + length, absv) - lisBegin;
    lis[idx] = absv;
    if (idx == length) ++length;
  }
}; // class LongestIncreasingSubsequence
}} // namespace cs::lis
