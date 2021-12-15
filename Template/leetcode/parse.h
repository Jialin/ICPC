#pragma once

#ifdef LOCAL
#include "common/macros.h"
#include "debug/debug_basic.h"
#include "leetcode/binary_tree.h"
#include "leetcode/interval.h"
#include "leetcode/linked_list.h"

using namespace std;

namespace leetcode {

namespace {

inline void _skipSpaces(const string& s, int& shift) {
  while (shift < SIZE(s)) {
    char ch = s[shift++];
    if (!ch) {
      DEBUGF_TRUE(false, "Expect - or digit @%d in \"%s\".\n", shift - 1, s.c_str());
      break;
    }
    if (!isspace(ch)) {
      --shift;
      break;
    }
  }
}

template<typename T>
inline void _parseInt(const string& s, int& shift, T& res) {
  char ch;
  _skipSpaces(s, shift);
  ch = s[shift];
  bool negative = ch == '-';
  if (negative) {
    ++shift;
  }
  res = 0;
  while (shift < SIZE(s)) {
    ch = s[shift++];
    if (!isdigit(ch)) {
      --shift;
      break;
    }
    res = (res << 3) + (res << 1) + (ch & 15);
  }
  if (negative) {
    res = -res;
  }
}

template<typename T>
inline bool _parseNullableInt(const string& s, int& shift, T& res) {
  _skipSpaces(s, shift);
  DEBUGF_TRUE(shift < SIZE(s), "'shift' out of bound. '%s'\n", s.c_str());
  if (s[shift] == 'n') {
    shift += 4;
    return false;
  } else {
    _parseInt(s, shift, res);
    return true;
  }
}

inline void _parse(const string& s, int& shift, int& v) {
  _parseInt(s, shift, v);
}

inline void _parse(const string& s, int& shift, char& v) {
  _skipSpaces(s, shift);
  DEBUGF_TRUE(
      shift < SIZE(s) && (s[shift] == '"' || s[shift] == '\''),
      "Expect begging '\"' or ''' @%d in '%s'\n",
      shift,
      s.c_str());
  ++shift;
  v = s[shift++];
  DEBUGF_TRUE(
      shift < SIZE(s) && (s[shift] == '"' || s[shift] == '\''),
      "Expect begging '\"' or ''' @%d in '%s'\n",
      shift,
      s.c_str());
  ++shift;
}

inline void _parse(const string& s, int& shift, string& v) {
  _skipSpaces(s, shift);
  DEBUGF_TRUE(
      shift < SIZE(s) && s[shift] == '"', "Expect begging '\"' @%d in '%s'\n", shift, s.c_str());
  ++shift;
  stringstream ss;
  while (shift < SIZE(s) && s[shift] != '"') {
    ss << s[shift++];
  }
  v = ss.str();
  DEBUGF_TRUE(
      shift < SIZE(s) && s[shift] == '"', "Expect ending '\"' @%d in '%s'\n", shift, s.c_str());
  ++shift;
}

inline void _parse(const string& s, int& shift, Interval& v) {
  _skipSpaces(s, shift);
  DEBUGF_TRUE(
      shift < SIZE(s) && s[shift] == '(', "Expect begging '(' @%d in '%s'\n", shift, s.c_str());
  ++shift;
  _parse(s, shift, v.start);
  DEBUGF_TRUE(
      shift < SIZE(s) && s[shift] == ',', "Expect begging ',' @%d in '%s'\n", shift, s.c_str());
  ++shift;
  _parse(s, shift, v.end);
  DEBUGF_TRUE(
      shift < SIZE(s) && s[shift] == ')', "Expect begging ')' @%d in '%s'\n", shift, s.c_str());
  ++shift;
}

template<typename T>
inline void _parse(const string& s, int& shift, vector<T>& res) {
  DEBUGF_TRUE(shift < SIZE(s), "'shift' out of bound. '%s'\n", s.c_str());
  _skipSpaces(s, shift);
  DEBUGF_TRUE(s[shift] == '[', "Expect '[' @%d in '%s'\n", shift, s.c_str());
  ++shift;
  res.clear();
  bool first = true;
  while (shift < SIZE(s)) {
    _skipSpaces(s, shift);
    if (s[shift] == ']') {
      ++shift;
      break;
    }
    if (first) {
      first = false;
    } else {
      DEBUGF_TRUE(s[shift] == ',', "Expect ',' @%d in '%s'\n", shift, s.c_str());
      ++shift;
    }
    T subRes;
    _parse(s, shift, subRes);
    res.push_back(move(subRes));
  }
}

} // namespace

template<typename T>
inline vector<T> parseVector(const string& s) {
  vector<T> res;
  int shift = 0;
  _parse(s, shift, res);
  return res;
}

ListNode* parseLinkedList(const string& s) {
  vector<int> vs;
  int shift = 0;
  _parse(s, shift, vs);
  ListNode* last = nullptr;
  for (int i = SIZE(vs) - 1; i >= 0; --i) {
    ListNode* node = new ListNode(vs[i]);
    node->next = last;
    last = node;
  }
  return last;
}

TreeNode* parseBinaryTree(const string& s) {
  DEBUGF_TRUE(!s.empty(), "Binary tree representation should not be empty\n");
  int shift = 0;
  DEBUGF_TRUE(s[shift] == '[', "Expect '[' @%d in '%s'\n", shift, s.c_str());
  ++shift;
  bool first = true;
  TreeNode* root = nullptr;
  deque<TreeNode*> q;
  while (shift < SIZE(s)) {
    if (s[shift] == ']') {
      break;
    }
    if (!first) {
      DEBUGF_TRUE(s[shift] == ',', "Expect ',' @%d in '%s'\n", shift, s.c_str());
      ++shift;
    }
    int subRes;
    if (_parseNullableInt(s, shift, subRes)) {
      auto* node = new TreeNode(subRes);
      q.push_back(node);
      if (first) {
        first = false;
        root = node;
        continue;
      }
      q.front()->left = node;
    }
    if (s[shift] == ']') {
      break;
    }
    DEBUGF_TRUE(s[shift] == ',', "Expect ',' @%d in '%s'\n", shift, s.c_str());
    ++shift;
    if (_parseNullableInt(s, shift, subRes)) {
      auto* node = new TreeNode(subRes);
      q.push_back(node);
      DEBUGF_TRUE(!q.empty(), "Expect the queue should not be empty. node val:%d\n", subRes);
      q.front()->right = node;
    }
    q.pop_front();
  }
  return root;
}

} // namespace leetcode
#endif
