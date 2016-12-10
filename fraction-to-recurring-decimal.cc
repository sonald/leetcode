#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

class Solution {
    public:
        string fractionToDecimal(int numerator, int denominator) {
            bool minus = (numerator < 0 ^ denominator > 0);
            long n = labs(numerator), d = labs(denominator);

            ostringstream os;
            if (minus) {
                os << "-";
            }
            os << n / d;

            n %= d;
            if (n == 0) return os.str();

            unordered_map<long, int> m;
            os << ".";
            m[n] = os.str().size();
            while (n) {
                n *= 10;
                os << n / d;
                n %= d;

                if (m.find(n) != m.end()) {
                    string s = os.str();
                    s.insert(m[n], "(");
                    s += ')';
                    return s;
                } else {
                    m[n] = os.str().size();
                }
            }

            return os.str();
        }
};

int main(int argc, char *argv[])
{
    cout << Solution().fractionToDecimal(4, 9) << endl;
    cout << Solution().fractionToDecimal(4, 333) << endl;
    cout << Solution().fractionToDecimal(16, 7) << endl;
    cout << Solution().fractionToDecimal(9, 13) << endl;
    cout << Solution().fractionToDecimal(9, 43) << endl;
    cout << Solution().fractionToDecimal(9, 113) << endl;

    cout << Solution().fractionToDecimal(1, 2) << endl;
    cout << Solution().fractionToDecimal(10, 6) << endl;
    cout << Solution().fractionToDecimal(1, 6) << endl;
    cout << Solution().fractionToDecimal(1, 8) << endl;
    cout << Solution().fractionToDecimal(1, 1024) << endl;
    cout << Solution().fractionToDecimal(2, 1) << endl;


    cout << Solution().fractionToDecimal(-2, 7) << endl;
    cout << Solution().fractionToDecimal(-2147483648, -1) << endl;
    cout << Solution().fractionToDecimal(-1, -2147483648) << endl;
    return 0;
}
