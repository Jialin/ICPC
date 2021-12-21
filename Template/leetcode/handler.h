#pragma once

#ifdef LOCAL
#include "leetcode/parse.h"

#ifndef FUNCITON_NAME
#define FUNCITON_NAME TODO
#endif

using namespace std;

namespace lc {

namespace {
const int ROW_SIZE = 100000;

char rawLine[ROW_SIZE];

} // namespace

template<typename Solution>
inline void handle(string tests) {
  istringstream ss(tests);
  int taskIdx = 0;
  while (true) {
    ++taskIdx;
    string line;
    while (!ss.eof()) {
      ss.getline(rawLine, ROW_SIZE);
      line = rawLine;
      if (!line.empty() && any_of(ALL(line), [](char c) {
            return !isspace(c);
          })) {
        break;
      }
    }
    if (ss.eof()) {
      break;
    }
#if ARGUMENT_CNT >= 1
    ARGUMENT_T_1 v1;
    parse(line, v1);
#endif
#if ARGUMENT_CNT >= 2
    ARGUMENT_T_2 v2;
    ss.getline(rawLine, ROW_SIZE);
    parse(rawLine, v2);
#endif
#if ARGUMENT_CNT >= 3
    ARGUMENT_T_3 v3;
    ss.getline(rawLine, ROW_SIZE);
    parse(rawLine, v3);
#endif
#if ARGUMENT_CNT >= 4
    ARGUMENT_T_4 v4;
    ss.getline(rawLine, ROW_SIZE);
    parse(rawLine, v4);
#endif
#if ARGUMENT_CNT >= 5
    ARGUMENT_T_5 v5;
    ss.getline(rawLine, ROW_SIZE);
    parse(rawLine, v5);
#endif

    cout << "===========================================================================\n";
    cout << "=====INPUT #" << taskIdx << "=====\n";
    DEBUGVS(
#if ARGUMENT_CNT >= 1
        v1
#endif
#if ARGUMENT_CNT >= 2
        ,
        v2
#endif
#if ARGUMENT_CNT >= 3
        ,
        v3
#endif
#if ARGUMENT_CNT >= 4
        ,
        v4
#endif
#if ARGUMENT_CNT >= 5
        ,
        v5
#endif
    );

    cout << "=====PROCESSING #" << taskIdx << "=====\n";
#if !RETURN_VOID
    auto res =
#endif
        Solution().FUNCTION_NAME(
#if ARGUMENT_CNT >= 1
            v1
#endif
#if ARGUMENT_CNT >= 2
            ,
            v2
#endif
#if ARGUMENT_CNT >= 3
            ,
            v3
#endif
#if ARGUMENT_CNT >= 4
            ,
            v4
#endif
#if ARGUMENT_CNT >= 5
            ,
            v5
#endif
        );

    cout << "=====OUTPUT #" << taskIdx << "=====\n";
    DEBUGVS(
#if ARGUMENT_CNT >= 1
        v1
#endif
#if ARGUMENT_CNT >= 2
        ,
        v2
#endif
#if ARGUMENT_CNT >= 3
        ,
        v3
#endif
#if ARGUMENT_CNT >= 4
        ,
        v4
#endif
#if ARGUMENT_CNT >= 5
        ,
        v5
#endif
    );
#if !RETURN_VOID
    DEBUGV3("!!!!!!", res, "!!!!!!");
#endif
  }

  {
    vector<int> v;
    parse("[1,2,1,2,6,7,5,1]", v);
  }
  {
    vector<string> v;
    parse(R"(["O  ", "   ", "   "])", v);
  }
  {
    vector<vector<int>> v;
    parse("[[2],[3,4],[6,5,7],[4,1,8,3]]", v);
  }
  {
    vector<vector<char>> v;
    parse(R"([["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]])", v);
  }
  {
    vector<Interval> v;
    parse("[(1,3),(2,6),(8,10),(15,18)]", v);
  }
  {
    ListNode* v;
    parse("[1,3,4,7,1,2,6]", v);
  }
  {
    ListNode* v;
    parse("[1,3,4,7,1,2,6]:2", v);
  }
  {
    TreeNode* v;
    parse("[5,1,2,3,null,6,4]", v);
  }
}

} // namespace lc
#endif
