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

//projection way
class Solution2 {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return;
        int rows = matrix.size(), cols = matrix[0].size();

        bool fr = false, fc = false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) {                
                    if (i == 0) fr = true;
                    if (j == 0) fc = true;
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (int i = 1; i < rows; i++) {
            if (matrix[i][0] == 0) {
                for (int k = 1; k < cols; k++) matrix[i][k] = 0;                  
            }
        }

        for (int j = 1; j < cols; j++) {
            if (matrix[0][j] == 0) {
                for (int k = 1; k < rows; k++) matrix[k][j] = 0;        
            }
        }

        if (fr) {
            for (int k = 0; k < cols; k++) matrix[0][k] = 0;               
        }

        if (fc) {
            for (int k = 0; k < rows; k++) matrix[k][0] = 0;               
        }

    }
};


class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return;
        int rows = matrix.size(), cols = matrix[0].size();

        int mark_row = -1, mark_col = -1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == mark_row || j == mark_col) continue;
                if (matrix[i][j] == 0) {
                    if (mark_row == -1) {
                        mark_row = i, mark_col = j;
                        for (int k = 0; k < rows; k++) {
                            if (matrix[k][j] == 0) matrix[k][j] = k+1;
                            else matrix[k][j] = 0;
                        }
                        for (int k = 0; k < cols; k++) {
                            if (matrix[i][k] == 0) matrix[i][k] = k+1;
                            else matrix[i][k] = 0;                                                      
                        }

                    } else {
                        matrix[i][mark_col] = i+1;
                        matrix[mark_row][j] = j+1;
                    }
                }
            }            
        }
        // cout << matrix << endl;

        if (mark_row == -1) return;

        for (int i = 0; i < rows; i++) {
            auto l = (matrix[i][mark_col]);
            if (l--) {
                for (int k = 0; k < cols; k++) matrix[l][k] = 0;                  
            }
        }

        for (int j = 0; j < cols; j++) {
            auto r = matrix[mark_row][j];
            if (r--) {
                for (int k = 0; k < rows; k++) matrix[k][r] = 0;        
            }
        }

    }
};

void test(vector<vector<int> > &matrix) {
    Solution2().setZeroes(matrix);
    cout << matrix << endl;
}

int main(int argc, char const *argv[])
{
    {
        vector<vector<int>> m {
            {0, 2, 3},
            {8, 1, 5}, 
            {0, 7, 1}
        };
        test(m);
    }
    {
        vector<vector<int>> m {
            {2, 1, 9, 8},
            {3, 8, 0, 2}, 
            {4, 1, 7, 3}
        };
        test(m);
    }
    {
        vector<vector<int>> m {
            {2, 1, 9},
            {3, 0, 8}, 
            {4, 1, 7}
        };
        test(m);
    }
    {
        vector<vector<int>> m {
            {1, 5, 1},
            {2, 1, 1}, 
            {3, 4, 1}
        };
        test(m);
    }
    return 0;
}