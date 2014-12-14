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

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    ::for_each(v.begin(), v.end(), [&](const T& s) { os << s << ","; });
    return os << "]";
}

class Solution {
    public:
        unordered_map<int, vector<string>> dp;
        vector<string> wordBreak(string s, unordered_set<string> &dict) {
            return helper(s, dict, 0, s.size());
        }

        vector<string> helper(string& s, unordered_set<string>& dict, int lo, int n) {
            //if (lo >= n) { return {}; }
            if (dp.find(lo) != dp.end()) return dp[lo];

            vector<string> res;
            for (int i = lo; i < n; i++) {
                string x = s.substr(lo, i-lo+1);
                if (dict.find(x) != dict.end()) {
                    if (i == n-1) { res.push_back(x); }
                    else {
                        vector<string> subs {helper(s, dict, i+1, n)};
                        for_each(subs.begin(), subs.end(), [&](const string& s) { 
                            res.push_back(x + " " + s);
                        });
                    }
                }
            }

            return dp[lo] = res;
        }
};

void test(string s, unordered_set<string> dict) 
{
    cout << Solution().wordBreak(s, dict) << endl;
}

int main(int argc, char *argv[])
{
    test("a", {"a"}); 
    test("leetcode", {"leet", "code"});
    test("aabbbcc", {"a", "ab", "bc", "abb", "bcc", "aab"}); 
    test("aaabbbcc", {"a", "ab", "bc", "abb", "bcc", "aab"}); 
    test("catsanddog",{"cat", "cats", "and", "sand", "dog"});
    test("aaaaaaa", {"aaaa","aa","a"});
    return 0;
}
