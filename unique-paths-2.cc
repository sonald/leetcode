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
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int m = obstacleGrid.size();
        if (!m) return 0;
        int n = obstacleGrid[0].size();
        if (!n) return 0;

        vector<vector<int>> v(m, std::vector<int>(n, 0));

        v[m-1][n-1] = 1;
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (obstacleGrid[i][j] == 1) v[i][j] = 0;
                else {
                    if (i < m-1) v[i][j] += v[i+1][j];
                    if (j < n-1) v[i][j] += v[i][j+1];
                }
            }
        }

        return v[0][0];
        
    }
};

void test(vector<vector<int> > &obstacleGrid) {
	cout << Solution().uniquePathsWithObstacles(obstacleGrid) << endl;
}

int main(int argc, char const *argv[])
{
    {
        vector<vector<int>> m {
            {0, 0, 0},
            {0, 1, 0}, 
            {0, 0, 1}
        };
        test(m);
    }
    {
        vector<vector<int>> m {
            {0, 0, 0},
            {0, 1, 0}, 
            {0, 1, 0}
        };
        test(m);
    }
    {
        vector<vector<int>> m {
            {0, 0, 0},
            {0, 1, 0}, 
            {0, 0, 0}
        };
        test(m);
    }
    return 0;
}
