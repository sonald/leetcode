#include <iostream>
#include <sstream>
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

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (auto& s: v) {
        os << s << ", ";
    }
    return os << "]";
}

#define VER 3

#if VER == 1
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        std::reverse(nums.begin(), nums.begin()+(n-k));
        std::reverse(nums.begin()+(n-k), nums.end());
        std::reverse(nums.begin(), nums.end());
    }

    void reverse(vector<int>& nums, int i, int j) {
    }
};
#elif VER == 2
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;

        vector<int> rep(n);
        for (int i = 0; i < n; i++) {
            rep[(i+k)%n] = nums[i%n];
        }

        nums = rep;
    }
};
#else
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;

        int start = 0, c = 0;
        int i = start;
        while (c < n) {
            int v = nums[i],t;
            do {
                t = nums[(i+k)%n];
                nums[(i+k)%n] = v;
                v = t;
                i = (i+k)%n;
                c++;
            } while (i != start);

            start++;
            i = start;
        }
    }
};
#endif

int main(int argc, char *argv[])
{
    
    vector<int> v;
    for (int k = 0; k <= 2; k++) {
        v = {1,2};
        Solution().rotate(v, k);
        cout << k << ": " << v << endl;
    }

    for (int k = 0; k <= 7; k++) {
        v = {1,2,3,4,5,6};
        Solution().rotate(v, k);
        cout << k << ": " << v << endl;
    }

    for (int k = 0; k <= 8; k++) {
        v = {1,2,3,4,5,6,7};
        Solution().rotate(v, k);
        cout << k << ": " << v << endl;
    }
    return 0;
}
