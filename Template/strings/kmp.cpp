namespace ss { namespace kmp {

template<typename T = char>
class KMP {
  int n;
  const T* pattern;
  vector<int> fail;

public:
  inline int calcNextPosition(int pos, T c) const {
    for (pos = pos == n - 1 ? fail[pos] : pos; pos >= 0 && pattern[pos + 1] != c; pos = fail[pos]) {}
    return pattern[pos + 1] == c ? pos + 1 : -1;
  }

  // Initializes fail
  inline void init(int _n, const T* _pattern) {
    this->n = _n;
    this->pattern = _pattern;
    fail.resize(n);
    fail[0] = -1;
    for (int i = 1; i < n; ++i) {
      fail[i] = calcNextPosition(fail[i - 1], pattern[i]);
    }
  }

  // Finds all occurence of matching patterns
  inline void findAll(int m, const T* s, vector<int>& matchStartPositions) {
    int pos = -1;
    for (int i = 0; i < m; ++i) {
      pos = calcNextPosition(pos, s[i]);
      if (pos == n - 1) matchStartPositions.push_back(i - n + 1);
    }
  }
}; // class KMP
}} // namespace ss::kmp
