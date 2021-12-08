// !macro_gen
// ALL LEETCODE_LINKED_LIST_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

#ifdef LOCAL
struct ListNode {
  int val;
  ListNode* next;
  inline ListNode() : val(0), next(nullptr) {}
  inline ListNode(int x) : val(x), next(nullptr) {}
  inline ListNode(int x, ListNode* next) : val(x), next(next) {}

  inline void _output(bool first, ostream& o) const {
    if (!first) {
      o << ',';
    }
    o << val;
    if (next) {
      next->_output(false, o);
    }
  }

  inline friend ostream& operator<<(ostream& o, const ListNode* node) {
    o << '[';
    if (node) {
      node->_output(true, o);
    }
    o << ']';
    return o;
  }
};
#endif

#ifdef LEETCODE_LINKED_LIST_CALC_LENGTH // ^
namespace leetcode {

inline int calcLength(const ListNode* head) {
  int res = 0;
  for (auto* node = head; node; node = node->next, ++res) {}
  return res;
}

} // namespace leetcode
#endif

#ifdef LEETCODE_LINKED_LIST_CALC_KTH // ^
namespace leetcode {

inline ListNode* calcKth(ListNode* head, int idx) {
  auto* node = head;
  FOR(i, 0, idx) {
    node = node->next;
  }
  return node;
}

} // namespace leetcode
#endif
