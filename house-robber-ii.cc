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

class Solution {
    public:
        int rob(vector<int>& nums) {
            int n = nums.size();
            if (n < 1) return 0;
            else if (n < 2) return nums[0];
            return max(rob1(nums, 0, n-2), rob1(nums, 1, n-1));
        }

    int rob1(vector<int>& nums, int l, int r) {
        int f0 = 0, f1 = 0;
        for (int i = l; i <= r; i++) {
            int t0 = std::max(f0, f1);
            f1 = f0 + nums[i];
            f0 = t0;
        }

        return std::max(f0, f1);
    }
};

int main(int argc, char *argv[])
{
    vector<int> v;
    {
        v = {2};
        cout << Solution().rob(v) << endl; // 2
    }
    {
        v = {2, 4};
        cout << Solution().rob(v) << endl; // 4
    }
    {
        v = {2, 4, 3};
        cout << Solution().rob(v) << endl; // 4
    }
    {
        v = {2, 3, 2};
        cout << Solution().rob(v) << endl; // 3
    }
    {
        v = {1, 2, 3, 1};
        cout << Solution().rob(v) << endl; // 4
    }
    {
        v = {1, 3, 1, 3, 100};
        cout << Solution().rob(v) << endl; // 103
    }
    {
        v = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        cout << Solution().rob(v) << endl; // 16
    }
    return 0;
}


