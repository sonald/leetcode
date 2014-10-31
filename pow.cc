#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

class Solution {
public:
    double pow(double x, int m) {
        bool reverse = m < 0;
        unsigned int n = m;
        if (m < 0) n = -m;
        double res = 1.0, r = x;
        while (n) {
            if (n & 0x1) {
                res *= r;
            }

            r *= r;
            n >>= 1;
        }

        return reverse ? 1.0/res:res;
    }
};

void test(double x, int n) {
    cout << x << "* " << n << ": " << Solution().pow(x, n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++)
        test(1.2, i);

    test(34.00515, -3);
    test(1.00000, -2147483648);
    test(-1.00000, -2147483648);
    test(-1.00000, -2147483);

	return 0;
}