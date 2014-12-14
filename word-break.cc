#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

ostream& operator<<(ostream& os, const unordered_set<string>& x)
{
    os << "(";
    ::for_each(x.begin(), x.end(), [&](const string& s) { os << s << ","; });
    return os << ")";
}

class Solution2 {
    public:
        bool wordBreak(string s, unordered_set<string> &dict) {
            int n = s.size();
            vector<int> dp(n, -1);

            return helper(s, dict, dp, 0, n) == 1;
        }

        int helper(string& s, unordered_set<string>& dict, vector<int>& dp,
                int lo, int n) {
            if (lo >= n) return 1;
            if (dp[lo] >= 0) return dp[lo];

            for (int i = lo; i < n; i++) {
                string x = s.substr(lo, i-lo+1);
                if (dict.find(x) != dict.end() && helper(s, dict, dp, i+1, n) == 1) {
                    return dp[lo] = 1; 
                }
            }

            return dp[lo] = 0;
        }
};

class Solution {
    public:
        bool wordBreak(string s, unordered_set<string> &dict) {
            int n = s.size();
            vector<vector<int>> dp(n, vector<int>(n, -1));

            return helper(s, dict, dp, 0, n-1) == 1;
        }

        int helper(string& s, unordered_set<string>& dict, vector<vector<int>>& dp,
                int lo, int hi) {
            if (lo > hi) return 1;
            if (dp[lo][hi] >= 0) return dp[lo][hi];

            for (int i = lo; i <= hi; i++) {
                string x = s.substr(lo, i-lo+1);
                if (dict.find(x) != dict.end()) {
                    dp[lo][i] = 1;
                    if (helper(s, dict, dp, i+1, hi) == 1) {
                        return dp[lo][hi] = 1; 
                    }
                }
            }

            return dp[lo][hi] = 0;
        }
};

void test(string s, unordered_set<string> dict) 
{
    cout << Solution2().wordBreak(s, dict) << endl;
    cout << Solution().wordBreak(s, dict) << endl;
}

int main(int argc, char *argv[])
{
    test("a", {"a"}); // 1?
    test("leetcode", {"leet", "code"}); // 1
    test("aabbbcc", {"a", "ab", "bc", "abb", "bcc", "aab"}); // 1
    test("aaabbbcc", {"a", "ab", "bc", "abb", "bcc", "aab"}); // 1
    test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"});
    return 0;
}
