#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int atoi(const char *str) {
            unsigned int r = 0;
            string s{str};

            auto f = ::find_if(s.begin(), s.end(), [](char c) { return !::isspace(c); });
            if (f == s.end()) return 0;

            bool positive = true;
            if (*f == '-' || *f == '+') {
                positive = *f == '+';
                f++;
            }

            auto i = ::find_if(f, s.end(), [](char c) {return ::isdigit(c); });
            if (i != f) return 0;

            auto j = ::find_if(i, s.end(), [](char c) { return !::isdigit(c); });
            ::for_each(i, j, [&](char c) { r = r * 10 + (c - '0'); });

            if (positive && r > 2147483647) return 2147483647;
            else if (!positive && r > 2147483648) return -2147483648;
            return positive ? r : -r;
        }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << "123 : " << sol.atoi("123 ") << endl;
    cout << "  : " << sol.atoi("   ") << endl;
    cout << "   123: " << sol.atoi("   123") << endl;
    cout << "ad123: " << sol.atoi("ad123") << endl;
    cout << "-123: " << sol.atoi("-123") << endl;
    cout << " -2147483649: " << sol.atoi(" -2147483649") << endl;
    cout << "     10522545459: " << sol.atoi("      10522545459") << endl;
    return 0;
}
