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
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;        
        int rows = matrix.size(), cols = matrix[0].size();

        int l = 0, r = rows-1;
        while (l <= r) {
            int m = l + (r-l)/2;
            if (matrix[m][0] == target) return true;
            else if (matrix[m][0] > target) {
                r = m-1;
            } else l = m+1;
        }

        int row = l-1;
        if (row < 0) return false;

        l = 0, r = cols-1;
        while (l <= r) {
            int m = l + (r-l)/2;
            if (matrix[row][m] == target) return true;
            else if (matrix[row][m] > target) {
                r = m-1;
            } else l = m+1;
        }

        return false;
    }
};

void test(vector<vector<int> > &matrix, int target) {
    cout << Solution().searchMatrix(matrix, target) << endl;
}

int main(int argc, char const *argv[])
{
    {
        vector<vector<int>> m {
            {1, 3}
        };
        test(m, 1);
        test(m, 3); 
    }
    cout << "------------" << endl;
    {
        vector<vector<int>> m {
            {1}
        };
        test(m, 1);
        test(m, 3); 
    }
    cout << "------------" << endl;
    {
        vector<vector<int>> m {
            {1,  3,  5,  7},
            {10, 11, 16, 20},
        };
        test(m, 0);
        test(m, 3); // 1
        test(m, 8);
        test(m, 11); // 1
        test(m, 30); 
        test(m, 21);
    }
    cout << "------------" << endl;
    {
        vector<vector<int>> m {
            {1,  3,  5,  7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
        };
        test(m, 0);
        test(m, 3); // 1
        test(m, 8);
        test(m, 11); // 1
        test(m, 30); // 1
        test(m, 21);
    }
    return 0;
}