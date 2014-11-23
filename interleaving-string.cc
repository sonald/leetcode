#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
    os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]\n";
}


template<class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	bool f = true;
	os << "{";
    for (auto& t: v) {
    	if (f) os << "(" << t.first << "," << t.second << ")";
    	else os << "," << "(" << t.first << "," << t.second << ")";
    }
    return os << "}";
}

// smarter: use only O(m) space
class Solution2 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size(), len = s3.size();
        if (n + m != len) return false;

        std::vector<int> dp(m+1, true);
        for (int i = 1; i <= m; i++) dp[i] = s2[i-1] == s3[i-1];            

        for (int i = 1; i <= n; i++) {
            dp[0] = s1[i-1] == s3[i-1];
            for (int j = 1; j <= m; j++) {
                auto v1 = s1[i-1], v2 = s2[j-1], r2 = s3[i+j-1];
                auto old = dp[j];
                dp[j] = false;
                if (v2 == r2) dp[j] = dp[j-1];
                if (!dp[j] && v1 == r2) dp[j] = old; // the last line
                
            }
        }
        // cout << dp << endl;
        return dp[m];
    }
};


class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size(), len = s3.size();
        if (n + m != len) return false;

        std::vector<vector<int>> dp(n+1, std::vector<int>(m+1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) dp[i][0] = s1[i-1] == s3[i-1];
        for (int i = 1; i <= m; i++) dp[0][i] = s2[i-1] == s3[i-1];            

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                auto v1 = s1[i-1], v2 = s2[j-1], r2 = s3[i+j-1];
                if (v2 == r2) dp[i][j] = dp[i][j-1];
                if (!dp[i][j] && v1 == r2) dp[i][j] = dp[i-1][j];
            }
        }
        // cout << dp << endl;
        return dp[n][m];
    }
};

void test(const string& s, const string& k, const string& s3) {
    cout << Solution().isInterleave(s, k, s3) << " ";    
    cout << Solution2().isInterleave(s, k, s3) << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    test("", "", ""); // 1
    test("aabcc", "dbbca", "aadbbcbcac"); // 1
    test("aabcc", "dbbca", "aadbbbaccc"); // 0
    test("a", "b", "ba"); // 1
    test("a", "", "a"); // 1
    test("aabd", "abdc", "aabdbadc"); // 0
    test("ab", "bc", "babc"); // 1
    test("aabc", "abad", "aabadabc"); // 1
    return 0;   
}