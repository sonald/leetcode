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
#include <sstream>

using namespace std;

#define VER 2

class Solution {
public:
#if VER == 1
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> c;

        int m = nums[0];
        for (auto i: nums) {
            c[i]++;
            if (c[i] > c[m]) {
                m = i;
            }
        }

        return m;
    }
#else
    int majorityElement(vector<int>& nums) {
        int max = 0;
        int count = 0;

        for (int i = 0, n = nums.size(); i < n; i++) {
            if (count == 0) {
                max = nums[i];
                count++;
            } else if (max != nums[i]) 
                count--;
            else count++;
        }

        return max;
    }
#endif
};

int main(int argc, char *argv[])
{
    vector<int> v;
    {
        v = {1, 2, 1};
        cout << Solution().majorityElement(v) << endl;
    }
    {
        v = {1, 2, 1, 3, 2, 2, 4};
        cout << Solution().majorityElement(v) << endl; //2
    }
    return 0;
}

