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
    int minPathSum(vector<vector<int> > &grid) {
         int m = grid.size();
        if (!m) return 0;
        int n = grid[0].size();
        if (!n) return 0;

        // vector<vector<int>> v(m, std::vector<int>(n, 0));
        auto& v = grid;
        
        v[m-1][n-1] = grid[m-1][n-1];
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (i == m-1 && j == n-1) continue;

                if (i == m-1) v[i][j] += v[i][j+1];
                else if (j == n-1) v[i][j] += v[i+1][j];
                else {
                    if (v[i+1][j] > v[i][j+1])
                        v[i][j] += v[i][j+1];
                    else 
                        v[i][j] += v[i+1][j];
                }
            }
        }

        // cout << v << endl;
        return v[0][0];
        
    }
};

void test(vector<vector<int> > &grid) {
	cout << Solution().minPathSum(grid) << endl;
}

int main(int argc, char const *argv[])
{
    {
        vector<vector<int>> m {
            {0, 0, 2},
            {4, 1, 0}, 
            {0, 7, 1}
        };
        test(m);
    }
    {
        vector<vector<int>> m {
            {2, 1, 2},
            {0, 1, 8}, 
            {2, 1, 0}
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
