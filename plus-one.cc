#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        vector<int> plusOne(vector<int>& digits) {
            reverse(digits.begin(), digits.end());

            auto sz = digits.size();
            vector<int> v(sz+1);

            int carry = 1;
            for (int i = 0; i < sz; ++i) {
                auto d = (digits[i] + carry);
                carry = d-9>0?1:0;
                v[i] = carry? d - 10 : d;
            }

            if (carry) {
                v[sz] = 1;
            } else {
                v.resize(sz);
            }

            ::reverse(v.begin(), v.end());
            return v;
        }
};

ostream& operator<<(ostream& os, const vector<int>& v)
{
    ::for_each(v.begin(), v.end(), [&](int x) { os << x; });
    return os;
}

int main(int argc, char *argv[])
{
    Solution sol;

    vector<int> v{1,3,7};
    cout << sol.plusOne(v) << endl;

    v = {9};
    cout << sol.plusOne(v) << endl;

    v = {9, 9};
    cout << sol.plusOne(v) << endl;

}
