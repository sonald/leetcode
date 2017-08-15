#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

template<class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	bool f = true;
	os << "{";
    for (auto& t: v) {
    	if (f) os << "(" << t.first << "," << t.second << ")";
    	else os << "," << "(" << t.first << "," << t.second << ")";
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << std::setw(3) << s << " ";
    }
    return os <<"]\n";
}

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int c = 0;
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    c++;
                    dfs(grid, i, j);
                }
            }
        }
        return c;
    }

    void dfs(vector<vector<char>>& grid, int i, int j) {
        int n = grid.size();
        int m = grid[0].size();
        if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == '0') {
            return;
        }

        grid[i][j] = '0';

        if (i > 0 && grid[i-1][j] == '1') {
            dfs(grid, i-1, j);
        }

        if (i < n-1 && grid[i+1][j] == '1') {
            dfs(grid, i+1, j);
        }

        if (j > 0 && grid[i][j-1] == '1') {
            dfs(grid, i, j-1);
        }

        if (j < m-1 && grid[i][j+1] == '1') {
            dfs(grid, i, j+1);
        }
    }
};

//flood fill
class Solution2 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int c = 0;
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();

        vector<vector<bool>> b(n, vector<bool>(m, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!b[i][j] && grid[i][j] == '1') {
                    c++;
                    b[i][j] = true;
                    helper(grid, b, i, j, c);
                }
            }
        }
        return c;

    }

    void helper(vector<vector<char>>& grid, vector<vector<bool>>& b, int i, int j, int &c) {
        int n = grid.size();
        int m = grid[0].size();

        if (i > 0 && !b[i-1][j] && grid[i-1][j] == '1') {
            b[i-1][j] = true;
            helper(grid, b, i-1, j, c);
        }

        if (i < n-1 && !b[i+1][j] && grid[i+1][j] == '1') {
            b[i+1][j] = true;
            helper(grid, b, i+1, j, c);
        }

        if (j > 0 && !b[i][j-1] && grid[i][j-1] == '1') {
            b[i][j-1] = true;
            helper(grid, b, i, j-1, c);
        }

        if (j < m-1 && !b[i][j+1] && grid[i][j+1] == '1') {
            b[i][j+1] = true;
            helper(grid, b, i, j+1, c);
        }
    }
};


int main(int argc, char *argv[])
{
    {
        vector<vector<char>> grid = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
        };

        cout << Solution().numIslands(grid) << std::endl;  // 1
        cout << Solution2().numIslands(grid) << std::endl;  // 1
    }

    {
        vector<vector<char>> grid = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'},
        };

        cout << Solution().numIslands(grid) << std::endl; // 3
        cout << Solution2().numIslands(grid) << std::endl;  // 3
    }

    {
        vector<vector<char>> grid = {
            {'0', '0', '0', '0', '0'},
            {'0', '1', '1', '1', '0'},
            {'1', '0', '0', '1', '0'},
            {'1', '1', '0', '0', '1'},
            {'0', '0', '0', '0', '1'},
        };

        cout << Solution().numIslands(grid) << std::endl; // 3
        cout << Solution2().numIslands(grid) << std::endl;  // 3
    }

    {
        vector<vector<char>> grid = {
            {'1', '1', '1'},
            {'0', '1', '0'},
            {'1', '1', '1'},
        };

        cout << Solution().numIslands(grid) << std::endl; // 1
        cout << Solution2().numIslands(grid) << std::endl;  // 1
    }

    return 0;
}
