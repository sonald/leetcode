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

class Solution {
public:
    static bool orderLessThan(const int &a, const int &b) {
        string s = to_string(a);
        string t = to_string(b);

        string l = s + t, m = t + s;
        return l < m;
    }

    string largestNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end(), orderLessThan);
        ostringstream os;

        bool zero = true;
        auto p = nums.rbegin();
        while (p != nums.rend()) {
            os << *p;
            if (*p) zero = false;
            p++;
        }

        if (zero) return "0";
        return os.str();
    }
};

int main(int argc, char *argv[])
{
    vector<int> v;
    {
        v = {3, 30, 34, 5, 9};
        cout << Solution().largestNumber(v) << endl; // 9534330.
    }
    {
        v = {543, 543541};
        cout << Solution().largestNumber(v) << endl; //  543543541
    }
    {
        v = {543, 5435439};
        cout << Solution().largestNumber(v) << endl; // 5435439543
    }
    {
        v = {543, 5435430};
        cout << Solution().largestNumber(v) << endl; // 5435435430
    }
    {
        v = {5, 59, 7, 50};
        cout << Solution().largestNumber(v) << endl; // 759550
    }

    {
        v = {5, 54, 7, 50};
        cout << Solution().largestNumber(v) << endl; // 755450
    }

    {
        v = {0, 0, 0};
        cout << Solution().largestNumber(v) << endl; // 0.
    }
    return 0;
}

