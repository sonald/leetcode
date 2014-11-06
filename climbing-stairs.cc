#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n == 0) return 0;
        std::vector<int> dp(n+1, 0); 
        dp[0] = 1; dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n];
    }
};

void test(int n) {
    cout << "n: " << n << ", " << Solution().climbStairs(n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 20; ++i)
        test(i);
    return 0;
}