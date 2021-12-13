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

  inline bool _containsLoop() const {
    auto* slow = this;
    auto* fast = this;
    do {
      if (fast && fast->next) {
        fast = fast->next->next;
      } else {
        return false;
      }
      slow = slow->next;
    } while (slow != fast);
    return true;
  }

  inline void
  _output(bool first, bool containsLoop, unordered_set<int64_t>& visited, ostream& o) const {
    if (!first) {
      o << ',';
    }
    o << val;
    auto address = int64_t(this);
    if (containsLoop) {
      o << "(@" << hex << address << dec << ')';
    }
    if (visited.count(address)) {
      o << "**LOOP**";
      return;
    }
    visited.insert(address);
    if (next) {
      next->_output(false, containsLoop, visited, o);
    }
  }

  inline friend ostream& operator<<(ostream& o, const ListNode* node) {
    o << '[';
    if (node) {
      unordered_set<int64_t> visited;
      node->_output(true, node->_containsLoop(), visited, o);
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

#ifdef LEETCODE_LINKED_LIST_CONTAINS_LOOP // ^
namespace leetcode {

inline bool containsLoop(ListNode* head) {
  if (!head) {
    return false;
  }
  auto* slow = head;
  auto* fast = head;
  do {
    if (fast->next) {
      fast = fast->next->next;
    } else {
      return true;
    }
    slow = slow->next;
  } while (slow != fast);
  return false;
}

#endif
