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

#define VER 2

#if VER == 1
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int f1 = 0, f2 = 0, f3 = nums[0], f = nums[1];
        for (int i = 2; i < n; i++) {
            f1 = f2;
            f2 = f3;
            f3 = f;
            f = std::max(f2 + nums[i], f1 + nums[i]);
        }
        return std::max(f, f3);
    }
};

#elif VER == 2
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        int f0 = 0, f1 = 0;
        for (int i = 0; i < n; i++) {
            int t0 = std::max(f0, f1);
            f1 = f0 + nums[i];
            f0 = t0;
        }

        return std::max(f0, f1);
    }
};

#elif VER == 3
//base
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        int max = std::numeric_limits<int>::min();
        int total = 0;
        rob(nums, n, 0, total, max);
        return max;
    }
            
    void rob(vector<int>& nums, int n, int idx, int& total, int& max) {
        if (idx >= n) {
            if (max < total) max = total;
        }
        for (int i = idx; i < n; i++) {
            total += nums[i];
            rob(nums, n, i+2, total, max);
            total -= nums[i];
        }
    }
};
#endif

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
        cout << Solution().rob(v) << endl; // 5
    }
    {
        v = {2, 8, 4};
        cout << Solution().rob(v) << endl; // 8
    }
    {
        v = {2, 8, 10, 4};
        cout << Solution().rob(v) << endl; // 12
    }
    {
        v = {2, 1, 1, 2 };
        cout << Solution().rob(v) << endl; // 4
    }
    {
        v = {104,209,137,52,158,67,213,86,141,110,
            151,127,238,147,169,138,240,185,246,225,
            147,203,83,83,131,227,54,78,165,180,214,
            151,111,161,233,147,124,143};
        cout << Solution().rob(v) << endl; // 3176
    }
    return 0;
}

