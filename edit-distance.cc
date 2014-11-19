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

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << std::setw(3) << s << " ";
    }
    return os <<"]\n";
}

// http://www.codeproject.com/Articles/13525/Fast-memory-efficient-Levenshtein-algorithm
// the above has a simple improve by using two vectors

class Solution2 {
public:
   int min(int v1, int v2, int v3) {
        return std::min(v1, std::min(v2, v3));
    }

    int minDistance(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        if (!n || !m) return max(n, m);
        std::vector<vector<int>> dp(n+1, vector<int>(m+1, 0)); // augmented
        for (int i = 0; i <= m; i++) dp[0][i] = i;
        for (int i = 0; i <= n; i++) dp[i][0] = i;  

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else 
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1; 
            }
        }

        // for (int i = 1; i <= m; i++) dp[0][i] = s2[i-1];
        // for (int i = 1; i <= n; i++) dp[i][0] = s1[i-1];  
        // for (int i = 0; i <= n; i++) {
        //     for (int j = 0; j <= m; j++) {
        //         if (!i && !j) cout << setw(3) << 0 << " ";
        //         else if (!i || !j) cout << setw(3) << (char)dp[i][j] << " ";
        //         else cout << setw(3) << dp[i][j] << " ";
        //     }
        //     cout << endl;
        // }            

        return dp[n][m];
    }
};

//naive way 
class Solution {
public:
    int res = INT_MAX;

    int minDistance(string word1, string word2) {
        return helper(word1, 0, word2, 0, 0);  
    }

    int changeFirst(string& s1, int i, string& s2, int j, int d) {
        auto ch1 = s1[i], ch2 = s2[j];
        d++;
        if (d >= res) { return d; }

        s1[i] = s2[j];
        auto v1 = helper(s1, i+1, s2, j+1, d);
        s1[i] = ch1;

        s1.erase(s1.begin()+i);
        auto v2 = helper(s1, i, s2, j, d);
        s1.insert(s1.begin()+i, ch1);

        s1.insert(s1.begin()+i, ch2);
        auto v3 = helper(s1, i+1, s2, j+1, d);
        s1.erase(s1.begin()+i);

        return min(v1, v2, v3) + 1;
    }

    // d is current distance
    int helper(string& s1, int i, string& s2, int j, int d) {
        if (i >= s1.size() || j >= s2.size()) {
            if (i >= s1.size() && j >= s2.size()) {
                res = std::min(d, res);
                return 0;            
            }
            auto v = abs((int)s1.size() - (int)s2.size());
            res = std::min(d+v, res);            
            return v;
        } 

        if (s1[i] == s2[j]) {
            return helper(s1, i+1, s2, j+1, d);
        } else {
            auto v1 = changeFirst(s1, i, s2, j, d);
            auto v2 = changeFirst(s2, j, s1, i, d);
            return std::min(v1, v2);
        }
    }

    int min(int v1, int v2, int v3) {
        return std::min(v1, std::min(v2, v3));
    }
};

void test(const string& s, const string& k) {
    cout << Solution2().minDistance(s, k) << " ";    
    cout << Solution().minDistance(s, k) << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    test("", ""); // 0    
    test("zoologicoarchaeologist", "zoogeologist"); // 10
    test("plasma", "altruism"); // 6
    test("", "help"); // 4
    test("a", "ba"); // 1
    test("a", "bl"); // 2
    test("gumbo", "gambol"); // 2
    test("hello", "hallo"); // 1
    test("hello", "hllo"); // 1
    return 0;    
}