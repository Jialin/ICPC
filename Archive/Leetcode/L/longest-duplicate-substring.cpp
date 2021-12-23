// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#ifdef LOCAL
// Typical types:
// - int
// - vector<int>
// - vector<vector<int>>
// - ListNode*
// - TreeNode*
// - Interval
#define FUNCTION_NAME longestDupSubstring
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"banana"
"abcd"
"peftxylsseopntszwuwrugksyrizvatuwgiarugnmypheecnproenzyksusehuujvnpqwwqnuhdogeqnfnhdbhatcuaaniteuwhsmpmrzfxekstssaynzzvmqwdhwtnizwiejjkfovscneouvjsljzfkmtrhunaxgcaswfajczlnhacsajozjwpoqjtdcaqsubbntxlpayebjfbzjiaoiyjbmzktcnscxyhpdkfexnjfrngjesbtwnmasnwvauzlzkompxkgifxsavzfhwvdjausccrjfpnzordyfgjdyawqzbfbizqvecrbhupkdudvxdknkqwjynyrutzhcnmfabwwaerdirsnufhlktojnyrefumfhvkolrybjpadpowjoqhhbzqpmpcmrddtrplgezihshtvpnqxikgsiiqnmezybjzktpdzsmribdkvlfbvicrgnblqnaylcijqbxjcnmjdrsfpcdojwcanvkgfaappivqnocobyeavoifqgnroagelmfjprxkupbdrwnycnhffgchclumhpxnlbbbmfsjmqoxuwkzwwksraxhlvdvrnjmfqzdksnxyhbaquxidvlgpjhlskrvkbsizyfedhwqsrzlwkesslvduwksoreufeflbgodatiblhmmfeiwbtohurgprremycvkhecakofsmpiimdcecpcvuseiqkxifzktkfnaqnpshcfdrhgjalpwaqumixmrxwduhgxwtfxarwyfshsutxihpecwbgzghkfaukdfbyecpryqxooyjsurjstfwrpegyxtdbkoicorqe"
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

const int64_t MOD = 288230376151711717;

class Solution {
public:
  int findDuplicate(int len, const string& s) {
    int n = s.size();
    vector<pair<int64_t, int>> hashs;
    int64_t modPow = 1;
    FOR(i, 1, len) {
      modPow = (modPow << 5) % MOD;
    }
    int64_t hash = 0;
    FOR(i, 0, len - 1) {
      hash = ((hash << 5) | (s[n - 1 - i] - 'a' + 1)) % MOD;
    }
    FORR(i, n - len, 0) {
      hash = ((hash << 5) | (s[i] - 'a' + 1)) % MOD;
      hashs.emplace_back(hash, i);
      hash -= modPow * (s[i + len - 1] - 'a' + 1) % MOD;
      if (hash < 0) {
        hash += MOD;
      }
    }
    SORT(hashs);
    FOR(i, 1, SIZE(hashs)) {
      if (hashs[i - 1].first == hashs[i].first) {
        return hashs[i].second;
      }
    }
    return -1;
  }

  string longestDupSubstring(string s) {
    int res = 0, resIdx = -1;
    int lower = 1, upper = s.size();
    while (lower < upper) {
      int medium = (lower + upper) >> 1;
      int idx = findDuplicate(medium, s);
      if (idx >= 0) {
        res = medium;
        resIdx = idx;
        lower = medium + 1;
      } else {
        upper = medium;
      }
    }
    return res ? s.substr(resIdx, res) : "";
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
