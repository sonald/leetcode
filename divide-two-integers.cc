#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]";
}

class Solution {
    public:
        inline int abs(int n) {
            if (n < 0) {
                if (n == INT_MIN) return INT_MAX;
                return -n;
            }
            return n;
        }
        int divide(int dividend, int divisor) {
            if (divisor == 0) return 0;
            if (divisor == INT_MIN) {
                if (dividend == INT_MIN) return 1;
                return 0;
            }

            int res = 0;
            int sign1 = (dividend >> 31) == 0? 1: -1;
            int sign2 = (divisor >> 31) == 0? 1: -1;
            bool may_of = (dividend == INT_MIN); // may overflow
            if (may_of && divisor == 1) return dividend;
            dividend = abs(dividend), divisor = abs(divisor);

            while (dividend > 0) {
                int exp = 0;
                while (dividend - (divisor<<exp) >= 0) exp++;
                if (--exp >= 0) res += (1<<exp);
                else break;
                // cout << "exp " << exp << endl;
                dividend -= divisor<<exp;
                if (may_of) {
                    dividend += 1;
                    may_of = false;
                }
            }

            return sign1 * sign2 * res;
        }
};

void test(int dividend, int divisor)
{
    Solution sol;
    cout << sol.divide(dividend, divisor) << endl;
}

int main(int argc, char *argv[])
{
    test(1, 1); // 1
    test(1, 2); // 0
    test(2, 0);  // 0
    test(4, 3);  // 1
    test(100, 3);  // 33
    test(30, 5);
    test(2, -2);
    test(2147483647, 1);
    test(-2147483648, 1);  // -2147483648
    test(-2147483648, 2);  // -1073741824
    test(-2147483648, -1);  // 2147483647
    test(-2147483648, -3); // 715827882
    test(2147483647, -2147483648); // 0
    test(INT_MIN, -2147483648); // 1    
    return 0;
}





