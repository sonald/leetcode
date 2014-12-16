#include <iostream>
#include <unordered_map>
#include <climits>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

template<class T>
ostream& operator<<(ostream& os, const pair<T, T>& p)
{
    return os << "(" << p.first << "," << p.second << ")";
}

template<class T, class U>
ostream& operator<<(ostream& os, const unordered_map<T, U>& v)
{
    os << "{";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << "(" << x.first << "=> " << x.second << ")";
    }
    return os << "}";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << x;
    }
    return os << "]";
}

// O(n) space, two pass
class Solution {
    public:
        int candy(vector<int> &ratings) {
            int n = ratings.size();
            if (n <= 0) return 0;

            vector<int> sp(n, 1);
            for (int i = 1; i < n; i++) {
                if (ratings[i-1] < ratings[i]) {
                    sp[i] = sp[i-1] + 1;
                } else sp[i] = 1;
            }

            int res = sp[n-1];
            for (int i = n-2; i >= 0; i--) {
                if (ratings[i+1] < ratings[i] && sp[i] <= sp[i+1]) {
                    sp[i] = sp[i+1] + 1;
                } 
                res += sp[i];
            }

            return res;
        }
};

void test(vector<int> ratings)
{
    cout << Solution().candy(ratings) << endl;
}

int main(int argc, char *argv[])
{
    test({}); // 0
    test({2}); // 1
    test({1,2,2}); // 4
    test({2,1,3,2,1}); // 9
    test({2,1,4,3,2,1}); // 13
    test({2,1,4,4,2,1}); // 11
    test({2,1,3,5,4,4,2,1,3}); // 17
    test({2,1,3,5,5,4,4,2,1,3}); // 19
    test({4,2,3,4,1}); // 9
    return 0;
}
