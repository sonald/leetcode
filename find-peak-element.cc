#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cassert>

using namespace std;
#define VERSION  2

#if VERSION == 1
class Solution {
    public:
        int findPeakElement(vector<int>& nums) {
            int len = nums.size();
            for (int i = 1; i < len; i++) {
                if (nums[i] < nums[i-1])
                    return i-1;
            }

            return len-1;
        }
};

#else
class Solution {
    public:
        int findPeakElement(vector<int>& nums) {

            return helper(nums, 0, nums.size() - 1);
        }

        int helper(vector<int>& v, int l, int r) {
            if (l == r) {
                return l;
            }

            int m = l + (r-l)/2;
            int vr = m == v.size()-1 ? INT_MIN : v[m+1];
            if (v[m] > vr) {
                return helper(v, l, m);
            } else {
                return helper(v, m+1, r);
            }
        }
};

#endif

int main(int argc, char *argv[])
{
    {
        vector<int> v = {1,2,3,1};
        Solution sol;
        cerr << sol.findPeakElement(v) << endl;
    }
    {
        vector<int> v = {1,3,2,1};
        Solution sol;
        cerr << sol.findPeakElement(v) << endl;
    }

    return 0;
}
