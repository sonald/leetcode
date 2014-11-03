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


//a little verbose though
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int>> matrix(n, std::vector<int>(n, 0));
        int m = n;
        int res = 1;

        for (int i = 0; i < m/2; ++i) {
            int j = i;
            outputRow(matrix, res, i, j, i, n-1-j);
            outputCol(matrix, res, i, n-1-j, m-i-1, n-1-j);
            outputRow(matrix, res, m-i-1, n-1-j, m-i-1, j, true);
            outputCol(matrix, res, m-i-1, j, i, j, true);
        }

        if (m & 1) {
            matrix[m/2][m/2] = n*n;
        }
        return matrix;
    }

    void outputCol(vector<vector<int> > &matrix, int& res, 
        int i1, int j1, int i2, int j2, bool reverse = false) {
        if (reverse) {
            for (int i = i1; i > i2; --i) {
                matrix[i][j1] = res++;
            }
        } else {
            for (int i = i1; i < i2; ++i) {
                matrix[i][j1] = res++;
            }
        }
    }

    void outputRow(vector<vector<int> > &matrix, int& res, 
        int i1, int j1, int i2, int j2, bool reverse = false) {
        if (reverse) {
            for (int j = j1; j > j2; --j) {
                matrix[i1][j] = res++;
            }
        } else {
            for (int j = j1; j < j2; ++j) {
                matrix[i1][j] = res++;
            }
        }
    }
};

void test(int n) {
    cout << Solution().generateMatrix(n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i <= 4; i++) {
        test(i);
    }
	return 0;
}