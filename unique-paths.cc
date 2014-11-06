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
    int uniquePaths(int m, int n) {
        vector<vector<int>> v(m, std::vector<int>(n, 0));
        if (!m || !n) return 0;

        v[m-1][n-1] = 1;
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (i < m-1) v[i][j] += v[i+1][j];
                if (j < n-1) v[i][j] += v[i][j+1];
            }
        }

        return v[0][0];
    }
};

void test(int m, int n) {
	cout << Solution().uniquePaths(m, n) << endl;
}

int main(int argc, char const *argv[])
{
    test(0, 0);
    test(1, 0);
    test(0, 1);
    test(1, 1);
    test(2, 2);
    test(3, 3);
    test(3, 7);
    test(100, 100);
    return 0;
}
