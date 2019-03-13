namespace trees { namespace trie {

template<int MAXL>
class Trie {
  int letterCnt;
  vector<int> children[MAXL];

  inline int createNode() {
    for (int i = 0; i < letterCnt; ++i) children[i].push_back(-1);
    return nodeCnt++;
  }

public:
  static const int ROOT = 0;
  int nodeCnt;

  // Initializes the trie with letter count
  inline void init(int _letterCnt) {
    letterCnt = _letterCnt;
    for (int i = 0; i < letterCnt; ++i) children[i].clear();
    nodeCnt = 0;
    createNode();
  }

  // Accesses the child and creates node when necessary
  inline int forceAccess(int idx, int letter) {
    int res = children[letter][idx];
    if (res < 0) res = createNode();
    return children[letter][idx] = res;
  }

  // Accesses the child
  inline int access(int idx, int letter) {
    return children[letter][idx];
  }
}; // class Trie
}} // namespace trees::trie
