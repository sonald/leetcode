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

ostream& operator<<(ostream& os, const vector<int>& v)
{
    os << "[";
    for (auto d: v) os << d << " ";
    return os << "]";
}

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();

        int c1 = 0, c2 = 0, m1 = -1, m2 = -1;
        for (int i = 0; i < n; i++) {
            if (m1 == nums[i]) {
                c1++;
            } else if (m2 == nums[i]) {
                c2++;
            } else if (c1 == 0) {
                m1 = nums[i]; c1++;
            } else if (c2 == 0) {
                m2 = nums[i]; c2++;
            } else {
                c1--, c2--;
            }
        }

        cerr << c1 << ", " << c2 << endl;
        c1 = 0, c2 = 0;
        for (int d : nums) {
            if (d == m1) c1++;
            else if (d == m2) c2++;
        }
        if (c1 > n/3) res.push_back(m1);
        if (c2 > n/3) res.push_back(m2);
        return res;
    }
};

int main(int argc, char *argv[])
{
    vector<int> v;
    {
        v = {0, 0, 0};
        cout << Solution().majorityElement(v) << endl;
    }
    {
        v = {1, 2, 3, 4};
        cout << Solution().majorityElement(v) << endl;
    }
    {
        v = {1, 2, 1};
        cout << Solution().majorityElement(v) << endl;
    }
    {
        v = {1, 2, 1, 3, 2, 2, 4};
        cout << Solution().majorityElement(v) << endl; //2
    }
    {
        v = {1, 2, 1, 3, 2, 2, 4, 1};
        cout << Solution().majorityElement(v) << endl; //2,1
    }
    {
        v = {8, 8, 7, 7, 7};
        cout << Solution().majorityElement(v) << endl; //7,8
    }
    {
        v = {1, 2, 2, 3, 2, 1, 1, 3};
        cout << Solution().majorityElement(v) << endl; //1, 2
    }
    return 0;
}


