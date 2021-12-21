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
namespace lc {

inline int calcLength(const ListNode* head) {
  int res = 0;
  for (auto* node = head; node; node = node->next, ++res) {}
  return res;
}

} // namespace lc
#endif

#ifdef LEETCODE_LINKED_LIST_CALC_KTH // ^
namespace lc {

inline ListNode* calcKth(ListNode* head, int idx) {
  auto* node = head;
  FOR(i, 0, idx) {
    node = node->next;
  }
  return node;
}

} // namespace lc
#endif

#ifdef LEETCODE_LINKED_LIST_REVERSE // ^
namespace lc {

inline ListNode* reverse(ListNode* head) {
  if (!head) {
    return nullptr;
  }
  ListNode* prev = nullptr;
  for (auto* cur = head; cur;) {
    auto* next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  return prev;
}

} // namespace lc
#endif

#ifdef LEETCODE_LINKED_LIST_TO_VECTOR // ^
namespace lc {

inline vector<int> toVector(ListNode* head) {
  vector<int> res;
  for (auto* node = head; node; node = node->next) {
    res.push_back(node->val);
  }
  return res;
}

} // namespace lc
#endif

#ifdef LEETCODE_LINKED_LIST_FROM_VECTOR // ^
namespace lc {

inline ListNode* fromVector(vector<int>& vs) {
  auto* dummyHead = new ListNode(-1);
  auto* tail = dummyHead;
  for (int v : vs) {
    auto* node = new ListNode(v);
    tail->next = node;
    tail = node;
  }
  return dummyHead->next;
}

} // namespace lc
#endif

#ifdef LEETCODE_LINKED_LIST_CONTAINS_LOOP // ^
namespace lc {

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

} // namespace lc
#endif
