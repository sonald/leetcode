
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <array>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

/**
 * Definition for an interval.
 */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

ostream& operator<<(ostream& os, const Interval& i)
{
    return os << "<" << i.start << "," << i.end << ">";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "{ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "}";
}

class Solution {
public:
    std::array<int, 10> facts;

    string getPermutation(int n, int k) {
        if (--k < 0) return "";
        string s;
        std::vector<int> nums;
        facts[0] = 1;
        for (int i = 1; i <= n; i++) { 
            facts[i] = facts[i-1] * i;
            nums.push_back(i);
        }

        while (n>1) {
            int a = k / facts[n-1];
            s += '0'+nums[a];
            auto e = std::remove(nums.begin(), nums.end(), nums[a]);
            // nums.erase(e, nums.end());

            k = k - a * facts[n-1];
            n--;
        }
        s += '0'+nums[0];
        return s;
    }
};

void test(int n, int k) {
    cout << Solution().getPermutation(n, k) << endl;
}

int main(int argc, char const *argv[])
{
    test(2, 1);
    test(1, 0);
    test(1, 1);
    int n = 9;
        for (int i = 1; i < 362880; ++i) {
            test(n, i);
        }
    return 0;
}