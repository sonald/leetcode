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
ostream& operator<<(ostream& os, const pair<int, int>& v)
{
    return os << "(" << v.first << "," << v.second << ")";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]";
}

template <class T, class U>
ostream& operator<<(ostream& os, const map<T, U>& v)
{
    os << "{";
    for (auto& x: v) {
        os << "{" << x.first << ", " << x.second << "} ";
    }
    return os << "}";
}

class Solution {
    public:
        int findMin(vector<int> &num) {
            int l = 0, r = num.size()-1;
            if (num[l] <= num[r]) return num[0];
            while (l <= r) {
                auto m = l+(r-l)/2;
                if (num[m] > num[m+1]) return num[m+1];
                if (num[0] > num[m]) { r = m-1; }
                else { l = m+1; }
            }
            return num[0];
        }
};

void test(vector<int> n) 
{
    cout << Solution().findMin(n) << endl;    
}

int main(int argc, char const *argv[])
{
	test({4, 5, 6, 7, 0, 1, 2});
	test({1, 2, 3, 4, 5});
	test({2, 3, 4, 5, 1});
	test({3, 4, 5, 1, 2});
	test({4, 5, 1, 2, 3});
    test({5, 1, 2, 3, 4}); 
    test({4, 5, 6, 7, 8, 1, 2, 3}); 
    test({2,1});
    test({1});

	return 0;
}
