// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "leetcode/binary_tree_macros.h"
#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/linked_list.h"
#include "leetcode/parse.h"

// Last include
#include "debug/debug.h"

const double PI = acos(-1.0);
const double PI2 = PI * 2;
const double EPS = 1E-8;

class Solution {
public:
  int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
    int resDelta = 0;
    vector<double> angles;
    for (const auto& point : points) {
      if (point == location) {
        ++resDelta;
      } else {
        angles.push_back(atan2(point[1] - location[1], point[0] - location[0]));
      }
    }
    SORT(angles);
    int anglesCnt = angles.size();
    FOR(i, 0, anglesCnt) {
      angles.push_back(angles[i] + PI2);
    }
    int pnt = 0, res = 0;
    double threshold = angle / 180.0 * PI + EPS;
    FORSIZE(i, angles) {
      for (; pnt < i && angles[i] - angles[pnt] > threshold; ++pnt) {}
      res = max(res, i - pnt + 1);
    }
    return min(res, anglesCnt) + resDelta;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<vector<char>>(
      "[[\"X\",\"X\",\"X\",\"X\"],[\"X\",\"O\",\"O\",\"X\"],[\"X\",\"X\","
      "\"O\",\"X\"],[\"X\",\"O\",\"X\",\"X\"]]");
  leetcode::parseVector<Interval>("[(1,3),(2,6),(8,10),(15,18)]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[2,1],[2,2],[3,3]]");
    auto v2 = leetcode::parseVector<int>("[1,1]");
    auto res = Solution().visiblePoints(v1, 90, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[2,1],[2,2],[3,4],[1,1]]");
    auto v2 = leetcode::parseVector<int>("[1,1]");
    auto res = Solution().visiblePoints(v1, 90, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
