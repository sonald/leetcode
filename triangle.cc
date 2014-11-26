#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
        os << s << " ";
    }
    return os <<"]";
}

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {        
        int n = triangle.size();
        if (!n) return 0;

        for (int l = n-2; l >= 0; l--) {
            auto& v = triangle[l];
            auto& v2 = triangle[l+1];
            for (int i = 0; i < v.size(); i++) {
                v[i] += min(v2[i], v2[i+1]);
            }
        }
        return triangle[0][0];
    }
};

class Solution2 {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        if (triangle.size() == 0) return 0;
        vector<vector<int>> dp(n+1, std::vector<int>(n+1, 0));

        for (int i = 1; i <= n; i++) 
            dp[n][i] = triangle[n-1][i-1];

        for (int i = n-1; i >= 1; i--) {
            for (int j = 1; j <= i; j++) {
                dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i-1][j-1];
            }
        }

        return dp[1][1];
    }
};

void test(vector<vector<int> > &triangle) {
    cout << Solution2().minimumTotal(triangle) << " ";        
    cout << Solution().minimumTotal(triangle) << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    {
        vector<vector<int>> v {
            {2},
            {3, 4},
            {6, 5, 7},
            {4, 1, 8, 3}
        };
        test(v);
    }
    return 0;    
}