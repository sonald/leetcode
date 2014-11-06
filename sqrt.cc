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
    int sqrt(int ix) {
        long long x = ix;
        if (x <= 1) return x;
        long long l = 0, r = x/2;
        long long m = 0;
        while (l < r) {
            m = l + (r-l)/2;
            long long mm = m * m;
            if (mm == x) return m;
            else if (mm > x) {
                r = m-1;
            } else l = m+1;
        }
        return l*l>x?l-1:l;
    }
};

int main(int argc, char const *argv[])
{
    for (int i = 0; i <= 100; i++)
        cout << "n = " << i << " " << Solution().sqrt(i) << endl;
    cout << Solution().sqrt(2147395599) << endl; // 46339
    cout << Solution().sqrt(10000) << endl; // 100
    return 0;
}
