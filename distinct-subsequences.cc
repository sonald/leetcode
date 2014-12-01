#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <array>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "{ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "}";
}

// O(m) space
class Solution3 {
    public:
        int numDistinct(string S, string T) {
            int m = T.size(), n = S.size();

            vector<int> dp (n+1, 0);
            for (int j = 1; j <= m; j++) {
                int prev = 0;
                for (int i = 1; i <= n; i++) {
                    auto old = dp[i];
                    dp[i] = 0;
                    if (S[i-1] == T[j-1]) {
                        if (j == 1) dp[i] = 1;
                        else dp[i] = prev;
                    } 
                    dp[i] += dp[i-1];
                    prev = old;
                }
            }

            return dp[n];
        }
};

// O(nm) rewrite of Solution 
class Solution2 {
    public:
        int numDistinct(string S, string T) {
            auto f = vector<vector<int>>(S.size()+1, vector<int>(T.size()+1, 0));
            int m = T.size(), n = S.size();

            for (int j = 1; j <= m; j++) {
                for (int i = 1; i <= n; i++) {
                    if (S[i-1] == T[j-1]) {
                        if (j == 1) f[i][j] = 1;
                        else f[i][j] = f[i-1][j-1];
                    } 
                    f[i][j] += f[i-1][j];

                }
            }

            return f[n][m];
        }
};

// memoization (top-down DP)
class Solution {
    public:
        vector<vector<int>> cache;
        int numDistinct(string S, string T) {
            cache = vector<vector<int>>(S.size()+1, vector<int>(T.size()+1, -1));
            return f(S, 0, T, 0);
        }

        int f(string& S, int i, string& T, int k) {
            if (k == T.size()) return 1;
            if (cache[i][k] >= 0) return cache[i][k];

            auto total = 0;
            for (int j = i, n = S.size(); j < n; j++) {
                if (S[j] == T[k]) {
                    total += f(S, j+1, T, k+1);
                }
            }
            return cache[i][k] = total;
        }
};

void test(string S, string T) {
    cout << Solution3().numDistinct(S, T) << endl;
    cout << Solution2().numDistinct(S, T) << endl;
}

int main(int argc, char const *argv[])
{
    test("rabbbit", "rabbit"); // 3
    test("bbabacb", "abc"); // 1
    test("abbcabacb", "abc"); // 6
    test("aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe", "bddabdcae");
    return 0;
}

