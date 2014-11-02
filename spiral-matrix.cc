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
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        int m = matrix.size();        
        if (m == 0) return {};
        int n = matrix[0].size();
        std::vector<int> res;

        for (int i = 0; i < m/2 && i < n/2; ++i) {
            int j = i;
            outputRow(matrix, res, i, j, i, n-1-j);
            outputCol(matrix, res, i, n-1-j, m-i-1, n-1-j);
            outputRow(matrix, res, m-i-1, n-1-j, m-i-1, j, true);
            outputCol(matrix, res, m-i-1, j, i, j, true);
        }

        if ((m&1) || (n&1)) {
            if (n > 1 && (m&1)) {
                int i = m / 2, j = i;                
                outputRow(matrix, res, i, j, i, n-j);
            } else {
                int j = n / 2, i = j;
                outputCol(matrix, res, i, j, m-i, j);
            }
        }
        return res;
    }

    void outputCol(vector<vector<int> > &matrix, vector<int>& res, 
        int i1, int j1, int i2, int j2, bool reverse = false) {
        if (reverse) {
            for (int i = i1; i > i2; --i) {
                res.push_back(matrix[i][j1]);
            }
        } else {
            for (int i = i1; i < i2; ++i) {
                res.push_back(matrix[i][j1]);
            }
        }
    }

    void outputRow(vector<vector<int> > &matrix, vector<int>& res, 
        int i1, int j1, int i2, int j2, bool reverse = false) {
        if (reverse) {
            for (int j = j1; j > j2; --j) {
                res.push_back(matrix[i1][j]);
            }
        } else {
            for (int j = j1; j < j2; ++j) {
                res.push_back(matrix[i1][j]);
            }
        }
    }
};


void test(std::vector<std::vector<int>>& matrix) {
    cout << Solution().spiralOrder(matrix) << endl;
}

int main(int argc, char const *argv[])
{
    {
        std::vector<std::vector<int>> matrix {
            {1, 11}, {2, 12}, {3, 13}, {4, 14}, 
            {5, 15}, {6, 16}, {7, 17}, {8, 18},
            {9, 19}, {10, 20}
        };
        test(matrix);
    }
    {
        std::vector<std::vector<int>> matrix {
            {1, 2, 3, },
            {5, 6, 7, },
            {9, 10, 11, },
            {13, 14, 15, }
        };
        test(matrix);
    }
    {
        std::vector<std::vector<int>> matrix {
            {7}, {9}, {6}
        };
        test(matrix);
    }
    {
        std::vector<std::vector<int>> matrix {
            {1, 2, 3, 4, 5},
        };
        test(matrix);
    }
    {
        std::vector<std::vector<int>> matrix {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
        };
        test(matrix);
    }
    {
        std::vector<std::vector<int>> matrix {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
        };
        test(matrix);
    }
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
	return 0;
}