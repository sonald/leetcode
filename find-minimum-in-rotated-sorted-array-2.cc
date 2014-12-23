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
            if (num.size() == 1) return num[0];
            return helper(num, 0, num.size()-1);
        }

        int helper(vector<int>& num, int l, int r) {
            if (l > r) return num[0];
            auto m = l+(r-l)/2;
            if (m < num.size()-1 && num[m] > num[m+1]) return num[m+1];
            if (num[l] < num[m])
                return helper(num, m+1, r);
            else if (num[l] > num[m])
                return helper(num, l, m-1);
            return min(helper(num, l, m-1), helper(num, m+1, r));
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

	test({1, 1, 2, 3, 4, 5});
	test({2, 3, 4, 5, 1, 1});
	test({2, 2, 2, 3, 4, 5, 1, 2});
	test({3, 3, 4, 5, 5, 1, 2});
	test({3, 3, 4, 5, 5, 1, 1, 3, 3});
	test({4, 4, 5, 1, 2, 3, 4, 4});
    test({5, 1, 2, 3, 4}); 

    test({1});
    test({1,3,1,1,1});
    test({2,1,2,2,2});
	return 0;
}
