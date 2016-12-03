#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]\n";
}

#define VERSION 1
#if VERSION == 1
using Grid = vector<vector<int>>;

class NumMatrix {
    public:
        NumMatrix(vector<vector<int>> &m) {
            if (m.size() == 0) return;

            int R = m.size(), C = m[0].size();

            _sums.resize(R+1);
            for (int r = 0; r < R+1; r++) {
                _sums[r].resize(m[0].size()+1);
            }

            for (int r = 0; r < R; r++) {
                for (int c = 0; c < m[0].size(); c++) {
                    _sums[r+1][c+1] = m[r][c] + _sums[r][c+1] + _sums[r+1][c] - _sums[r][c];
                }
            }

            //cout << _sums;
        }

        int sumRegion(int row1, int col1, int row2, int col2) {
            row2++;
            col2++;
            return _sums[row2][col2] - _sums[row1][col2] - _sums[row2][col1] + _sums[row1][col1];
        }

    private:
        Grid _sums;

};


#elif VERSION == 2
#endif

int main(int argc, char *argv[])
{
    vector<vector<int>> nums = {  
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };

    NumMatrix m(nums);
    cout << m.sumRegion(2, 1, 4, 3) << endl; // -> 8
    cout << m.sumRegion(1, 1, 2, 2) << endl; // -> 11
    cout << m.sumRegion(1, 2, 2, 4) << endl; // -> 12

    return 0;
}
