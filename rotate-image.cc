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
        os << t << "  ";
    }
    return os << "]\n";
}

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        vector<vector<bool>> done (n, vector<bool>(n, false));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                int t = matrix[i][j];
                if (done[i][j]) continue;
                int ii = j, jj = n-1-i;
                while (!done[ii][jj]) {
                    int r = matrix[ii][jj];
                    matrix[ii][jj] = t;
                    done[ii][jj] = true;
                    int tmp = ii; ii = jj; jj = n-1-tmp;
                    t = r;
                }
            }            
        }
    }
};

class Solution2 {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        auto& m = matrix;

        for (int i = 0; i < n/2; ++i) {
            for (int j = i; j < n-1-i; j++) {
                int t = m[i][j];
                m[i][j] = m[n-1-j][i];
                m[n-1-j][i] = m[n-1-i][n-1-j];
                m[n-1-i][n-1-j] = m[j][n-1-i];
                m[j][n-1-i] = t;
            }            
        }
    }
};

void test(std::vector<std::vector<int>>& matrix) {
    Solution().rotate(matrix);
    // cout << matrix << endl;
}

int main(int argc, char const *argv[])
{
    {
        std::vector<std::vector<int>> matrix {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        };
        test(matrix);
    }
    {
        std::vector<std::vector<int>> matrix {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}
        };
        test(matrix);
    }
    {
        int n = 2000;
        std::vector<std::vector<int>> matrix(n);
        for (int i = 0; i < n; ++i) {
            matrix[i] = std::vector<int>(n);
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = i*n+j;
            }
        }
        test(matrix);
    }
	return 0;
}