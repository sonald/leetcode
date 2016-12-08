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

ostream& operator<< (ostream& os, const vector<int>& v)
{
    os << "[";
    for(auto d: v) {
        os << d << " ";
    }
    return os << "]";
}

#define VER 2
#if VER == 1
//binary search
class Solution {
public:
    vector<int> twoSum(vector<int>& v, int target) {
        int n = v.size();
        for (int d = 1; d < n; d++) {
            int i1 = 0;
            if (match(v, 0, n-d-1, d, i1, target)) {
                return {i1+1, i1+d+1};
            }
        }

        return {1, 2};
    }

    bool match(vector<int>& v, int l, int r, int d, int& i1, int target) {
        while (l <= r) {
            int m = l + (r-l)/2;
            int res = v[m] + v[m+d];
            if (res == target) {
                i1 = m;
                return true;
            } else if (res < target) {
                l = m+1;
            } else {
                r = m-1;
            }
        }

        return false;
    }
};
#else
//two-pointers 
class Solution {
public:
    vector<int> twoSum(vector<int>& v, int target) {
        int n = v.size();
        int l = 0, r = n-1;
        while (l < r) {
            int res = v[l] + v[r];
            if (res == target) 
                return {l+1, r+1};
            else if (res > target) 
                r--;
            else
                l++;
        }

        return {1,2};
    }
};
#endif

int main(int argc, char *argv[])
{
    vector<int> v;
    int t;
    {
        v = {3, 4};
        t = 7;
        cout << Solution().twoSum(v, t) << endl;
    }

    {
        v = {2, 3, 4};
        t = 6;
        cout << Solution().twoSum(v, t) << endl;
    }

    {
        v = {2, 7, 11, 15};
        t = 22;
        cout << Solution().twoSum(v, t) << endl;
    }

    {
        v = {2, 7, 11, 15};
        t = 9;
        cout << Solution().twoSum(v, t) << endl;
    }

    {
        v = {2, 7, 11, 15, 17, 19, 20};
        t = 35;
        cout << Solution().twoSum(v, t) << endl;
    }
    return 0;
}

