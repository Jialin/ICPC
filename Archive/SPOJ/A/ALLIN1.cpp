#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
bool tight;
namespace ds {
template<typename NODE_V, typename RANGE_V = NODE_V, typename KEY = int>
struct BaseTreap {
  struct _Node {
    KEY _key;
    int _priority, _lIdx, _rIdx;
    NODE_V _v;
    RANGE_V _rangeV;
    inline _Node(const KEY& key) : _key(key), _priority(rand()), _lIdx(-1), _rIdx(-1) {}
  };
  virtual inline void _initRangeV(RANGE_V& res) = 0;
  virtual inline void _initV(_Node& node) = 0;
  virtual inline void _updateV(_Node& node, const NODE_V& delta) = 0;
  virtual inline void _mergeRangeV(_Node& node) = 0;
  virtual inline void _appendNode(RANGE_V& res, const _Node& idx) = 0;
  virtual inline void _appendRange(RANGE_V& res, const _Node& idx) = 0;
  inline BaseTreap() {
    init();
  }
  inline void clear() {
    _roots.assign(_rootCnt, -1);
    _nodes.clear();
  }
  inline void init() {
    _rootCnt = 1;
    clear();
  }
  inline void reserveNodes(int n) {
    _nodes.reserve(n);
  }
  inline int _newNode(const KEY& key, const NODE_V& delta) {
    int idx = static_cast<int>((_nodes).size());
    _nodes.emplace_back(key);
    auto& node = _nodes.back();
    _initV(node);
    _updateV(node, delta);
    return idx;
  }
  inline void update(const KEY& key, const NODE_V& delta) {
    _roots[0] = _update(_roots[0], key, delta);
  }
  inline int _update(int idx, const KEY& key, const NODE_V& delta) {
    if (idx < 0) {
      return _newNode(key, delta);
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      _updateV(node, delta);
      return idx;
    }
    if (key < node._key) {
      int newIdx = _update(node._lIdx, key, delta);
      auto& node2 = _nodes[idx];
      node2._lIdx = newIdx;
      if (_nodes[newIdx]._priority > node2._priority) {
        _rotateLeft(idx, newIdx);
        return newIdx;
      }
    } else {
      int newIdx = _update(node._rIdx, key, delta);
      auto& node2 = _nodes[idx];
      node2._rIdx = newIdx;
      if (_nodes[newIdx]._priority > node2._priority) {
        _rotateRight(idx, node2._rIdx);
        return newIdx;
      }
    }
    _mergeRangeV(_nodes[idx]);
    return idx;
  }
  inline void _rotateLeft(int idx, int lIdx) {
    auto& node = _nodes[idx];
    auto& lNode = _nodes[lIdx];
    node._lIdx = lNode._rIdx;
    lNode._rIdx = idx;
    _mergeRangeV(node);
    idx = lIdx;
    _mergeRangeV(lNode);
  }
  inline void _rotateRight(int idx, int rIdx) {
    auto& node = _nodes[idx];
    auto& rNode = _nodes[rIdx];
    node._rIdx = rNode._lIdx;
    rNode._lIdx = idx;
    _mergeRangeV(node);
    idx = rIdx;
    _mergeRangeV(rNode);
  }
  inline void erase(const KEY& key) {
    _roots[0] = _erase(_roots[0], key);
  }
  inline int _erase(int idx, const KEY& key) {
    if (idx < 0) {
      return -1;
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      return _merge(node._lIdx, node._rIdx);
    }
    if (key < node._key) {
      node._lIdx = _erase(node._lIdx, key);
    } else {
      node._rIdx = _erase(node._rIdx, key);
    }
    _mergeRangeV(node);
    return idx;
  }
  inline int _merge(int lIdx, int rIdx) {
    if (lIdx < 0) {
      return rIdx;
    }
    if (rIdx < 0) {
      return lIdx;
    }
    auto& lNode = _nodes[lIdx];
    auto& rNode = _nodes[rIdx];
    if (lNode._priority > rNode._priority) {
      lNode._rIdx = _merge(lNode._rIdx, rIdx);
      _mergeRangeV(lNode);
      return lIdx;
    } else {
      rNode._lIdx = _merge(lIdx, rNode._lIdx);
      _mergeRangeV(rNode);
      return rIdx;
    }
  }
  inline RANGE_V calcPrefix(const KEY& upper) {
    RANGE_V res;
    _initRangeV(res);
    _calcPrefix(_roots[0], upper, res);
    return res;
  }
  inline void _calcPrefix(int idx, const KEY& upper, RANGE_V& res) {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    if (node._key == upper) {
      tight = true;
    }
    if (node._key < upper) {
      if (node._lIdx >= 0) {
        _appendRange(res, _nodes[node._lIdx]);
      }
      _appendNode(res, node);
      _calcPrefix(node._rIdx, upper, res);
    } else {
      _calcPrefix(node._lIdx, upper, res);
    }
  }
  template<typename KTH>
  inline const _Node* calcKth(const KTH& kth) {
    return _calcKth(_roots[0], kth);
  }
  template<typename KTH>
  inline const _Node* _calcKth(int idx, KTH kth) {
    if (idx < 0 || kth < 0 || !(kth < _nodes[idx]._rangeV)) {
      return nullptr;
    }
    while (true) {
      const auto& node = _nodes[idx];
      if (node._lIdx >= 0) {
        const auto& lNode = _nodes[node._lIdx];
        if (kth < lNode._rangeV) {
          idx = node._lIdx;
          continue;
        }
        kth -= lNode._rangeV;
      }
      RANGE_V tmpRangeV;
      _initRangeV(tmpRangeV);
      _appendNode(tmpRangeV, node);
      if (kth < tmpRangeV) {
        return &node;
      }
      kth -= tmpRangeV;
      idx = node._rIdx;
    }
    return nullptr;
  }
  vector<_Node> _nodes;
  vector<int> _roots;
  int _rootCnt;
};
template<typename KEY = int>
struct TreapSet : BaseTreap<nullptr_t, int, KEY> {
  inline void insert(const KEY& key) {
    this->update(key, nullptr);
  }
  using _Node = typename TreapSet::_Node;
  inline void _initRangeV(int& res) override {
    res = 0;
  }
  inline void _initV(_Node& node) override {
    node._rangeV = 0;
  }
  inline void _updateV(_Node& node, const nullptr_t& delta) override {
    _mergeRangeV(node);
  }
  inline void _mergeRangeV(_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + 1 +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }
  inline void _appendNode(int& res, const _Node& node) override {
    ++res;
  }
  inline void _appendRange(int& res, const _Node& node) override {
    res += node._rangeV;
  }
};
} // namespace ds
namespace io {
const int _kReadBufferSize = 1 << 15;
char _readBuffer[_kReadBufferSize];
int _readPos;
int _readLength;
bool _ended = false;
inline void _loadBuffer() {
  _readLength = static_cast<int>(fread(_readBuffer, sizeof(char), _kReadBufferSize, stdin));
  _readPos = 0;
}
inline char readChar(bool advance = true) {
  if (_ended) {
    return 0;
  }
  if (_readPos >= _readLength) {
    _loadBuffer();
    if (_readLength == 0) {
      _ended = true;
      return 0;
    }
  }
  return _readBuffer[advance ? _readPos++ : _readPos];
}
template<typename T>
inline bool readInt(T& res) {
  char ch;
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return false;
    }
    if (!isspace(ch)) {
      break;
    }
    ++_readPos;
  }
  ch = readChar(false);
  bool negative = ch == '-';
  if (negative) {
    ++_readPos;
  }
  res = 0;
  while (true) {
    ch = readChar(false);
    if (!isdigit(ch)) {
      break;
    }
    res = (res << 3) + (res << 1) + (ch & 15);
    ++_readPos;
  }
  if (negative) {
    res = -res;
  }
  return true;
}
const int _kWriteBufferSize = 1 << 15;
int _writePos = 0;
char _writeBuffer[_kWriteBufferSize];
inline void writeChar(char x) {
  if (_writePos == _kWriteBufferSize) {
    fwrite(_writeBuffer, 1, _kWriteBufferSize, stdout);
    _writePos = 0;
  }
  _writeBuffer[_writePos++] = x;
}
struct _Flusher {
  inline void flush() {
    if (_writePos) {
      fwrite(_writeBuffer, 1, _writePos, stdout);
      _writePos = 0;
    }
    fflush(stdout);
  }
  inline ~_Flusher() {
    flush();
  }
} _flusher;
template<class T>
inline void writeInt(T x, int padding = 0) {
  static char s[32];
  if (x < 0) {
    writeChar('-');
    x = -x;
  }
  int n = 0;
  while (x || !n) {
    T newX = x / 10;
    s[n++] = '0' + (x - newX * 10);
    x = newX;
  }
  for (int i = n; i < padding; ++i) {
    writeChar('0');
  }
  for (; n > 0; writeChar(s[--n])) {}
}
} // namespace io
const int MAXN = 3000000;
int main() {
  ds::TreapSet<int> treap;
  treap.reserveNodes(MAXN);
  int op;
  while (io::readInt(op) && op > 0) {
    int x;
    io::readInt(x);
    --x;
    if (op == 1) {
      treap.insert(x);
    } else if (op == 2) {
      treap.erase(x);
    } else if (op == 3) {
      tight = false;
      int res = treap.calcPrefix(x);
      io::writeInt(tight ? res + 1 : -1);
      io::writeChar('\n');
    } else {
      const auto* res = treap.calcKth(x);
      io::writeInt(res ? res->_key + 1 : -1);
      io::writeChar('\n');
    }
  }
}
