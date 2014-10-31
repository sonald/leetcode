#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    ::for_each(v.begin(), v.end(), [&](const T& t) { os << "(" << t.first
            << "," << t.second << "),"; });
    return os << "]";
}

class Solution {
    public:
        //O(n)
        int maxArea(vector<int> &height) {
            size_t len = height.size();
            int ma = 0, l = 0, r = len-1;
            
            while (l < r) {
                int area = min(height[l], height[r]) * (r - l);
                ma = max(ma, area);
                if (height[l] > height[r]) {
                    r--;
                } else {
                    l++;
                }
            }

            return ma;
        }

        //O(nlgn)
        int maxArea2(vector<int> &height) {
            size_t len = height.size();
            int ma = 0, lhs = len, rhs = 0;

            using seq = pair<int, int>;
            vector<seq> copy;
            for (int i = 0; i < len; ++i) {
                copy.push_back({i, height[i]});
            }

            ::sort(copy.begin(), copy.end(), [&](const seq& t1, const seq& t2) {
                    return t1.second > t2.second;
                });
            cout << copy << endl;
            
            for (int i = 0; i < len; ++i) {
                seq e = copy[i];
                lhs = min(lhs, e.first), rhs = max(rhs, e.first);
                int area = (rhs-lhs) * e.second;
                if (ma < area) ma = area;
            }

            return ma;
        }
};

void test(vector<int> v)
{
    Solution sol;
    cout << sol.maxArea(v) << endl;
}

int main(int argc, char *argv[])
{
    test({1,2,1,3});
    test({2,5,3,1,5,6,4});
    test({1,2,3,4,5,6});
    return 0;
}
