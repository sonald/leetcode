#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

template<class T>
ostream& operator<<(ostream& os, const pair<T, T>& p)
{
    return os << "(" << p.first << "," << p.second << ")";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else
            os << ",";
        os << x;
    }
    return os << "]";
}

// we can get rid of dp to use only O(n) space and just compute ispal on the fly
// in the cuts. but that causes TLE.
class Solution2 {
    public:
        bool ispal(string& s, int i, int j) {
            while (i < j) {
                if (s.at(i) != s.at(j)) return false;
                i++, j--;
            }
            return true;
        }

        vector<vector<int>> dp;
        int minCut(string s) {
            int n = s.size();
            if (n == 0) return 0;

            dp = vector<vector<int>>(n, vector<int>(n, 0));
            for (int i = 0; i < n; i++) {
                dp[i][i] = 1;
                if (i < n-1 && s[i] == s[i+1]) dp[i][i+1] = 1;
            }

            for (int l = 3; l <= n; l++) {
                for (int i = 0; i < n-l+1; i++) {
                    auto& x = dp[i][i+l-1];
                    if (dp[i+1][i+l-2] && s.at(i) == s.at(i+l-1)) x = 1;
                }
            }

            vector<int> f(n, -1);
            return cuts(s, f, 0);
        }

        int cuts(string& s, vector<int>& f, int i) {
            int n = s.size();
            if (i >= n-1) { return 0; }
            if (f[i] >= 0) return f[i];

            //if (ispal(s, i, n-1)) return f[i] = 0;
            if (dp[i][n-1]) return f[i] = 0;
            int res = INT_MAX;
            for (int j = i; j < n; j++) {
                //if (ispal(s, i, j)) {
                if (dp[i][j]) {
                    res = min(res, cuts(s, f, j+1)+1);
                    if (res == 1) { return f[i] = 1; }
                }
            }

            return f[i] = res;
        }
};

class Solution {
    public:
        int minCut(string s) {
            if(s.empty()) return 0;
            int n = s.size();
            vector<vector<bool>> dp(n,vector<bool>(n,false));
            vector<int> f(n);
            for(int i=n-1;i>=0;i--) {
                f[i]=n-i-1;
                for(int j=i;j<n;j++) {
                    if(s[i]==s[j] && (j-i<2 || dp[i+1][j-1])) {
                        dp[i][j]=true;
                        if(j==n-1) f[i]=0;
                        else if(f[j+1]+1<f[i]) f[i]=f[j+1]+1;
                    }
                }
            }
            return f[0];
        }
};

void test(string s)
{
    cout << Solution().minCut(s) << " ";
    cout << endl;
    //cout << Solution2().minCut(s) << endl;
}

int main(int argc, char *argv[])
{
    test(""); // 0
    test("aaba"); // 1
    test("aa"); // 0
    test("a"); // 0
    test("aab"); // 1
    test("aabaa"); // 0
    test("seeslaka"); // 2
    test("seeslaveidemonstrateyetartsnomedieva"); // 2
    test("seeslaveidemonstrateyetartsnomedievalsees"); // 0
    return 0;

    test("fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi"); // 75
    test("adabdcaebdcebdcacaaaadbbcadabcbeabaadcbcaaddebdbddcbdacdbbaedbdaaecabdceddccbdeeddccdaabbabbdedaaabcdadbdabeacbeadbaddcbaacdbabcccbaceedbcccedbeecbccaecadccbdbdccbcbaacccbddcccbaedbacdbcaccdcaadcbaebebcceabbdcdeaabdbabadeaaaaedbdbcebcbddebccacacddebecabccbbdcbecbaeedcdacdcbdbebbacddddaabaedabbaaabaddcdaadcccdeebcabacdadbaacdccbeceddeebbbdbaaaaabaeecccaebdeabddacbedededebdebabdbcbdcbadbeeceecdcdbbdcbdbeeebcdcabdeeacabdeaedebbcaacdadaecbccbededceceabdcabdeabbcdecdedadcaebaababeedcaacdbdacbccdbcece"); // 273
    test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    return 0;
}
