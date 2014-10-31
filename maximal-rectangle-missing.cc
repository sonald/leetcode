#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    bool f = true;
    os << "[";
    ::for_each(v.begin(), v.end(), [&](const T& t) { 
        if (!f) os << "," << t;
        else os << t;
    });
    return os << "]";
}

class Solution {
    public:
        struct Rect {
            int x, y;
            size_t w, h;
        };

        int maximalRectangle(vector<vector<char> > &matrix) {
            if (matrix.size() == 0) return 0;

            vector<int> rowc(matrix.size());
            vector<int> colc(matrix[0].size());
            
            for (int i = 0, len = matrix.size(); i < len; ++i) {
                auto row = matrix[i];
                for (int j = 0, len2 = row.size(); j < len2; ++j) {
                    colc[j] += (row[j] == '1'? 1: 0);
                    rowc[i] += (row[j] == '1'? 1: 0);
                }
            }

            cerr << "rowc: " << rowc << endl;
            cerr << "colc: " << colc << endl;

            Rect r {0, 0, colc.size(), rowc.size()};
            auto i = ::find_if(rowc.begin(), rowc.end(), [&](int v) { return v > 0; });
            if (i == rowc.end()) return 0;
            r.y = i - rowc.begin();
            for (auto j = rowc.rbegin(); j != rowc.rend(); ++j) {
                if (*j > 0) {
                    r.h = (rowc.rend() - j); break;
                }
            }

            i = ::find_if(colc.begin(), colc.end(), [&](int v) { return v > 0; });
            if (i == colc.end()) return 0;
            r.x = i - colc.begin();
            for (auto j = colc.rbegin(); j != colc.rend(); ++j) {
                if (*j > 0) {
                    r.w = (colc.rend() - j); break;
                }
            }

            cerr << "r: " << r.x << " " << r.y << " " << r.w << " " << r.h << endl;
            return (r.w - r.x) * (r.h - r.y);
        }
};

int main(int argc, char *argv[])
{
    Solution sol;

    vector<vector<char>> m {
        {'0', '0', '0'},
        {'0', '1', '0'},
        {'1', '0', '0'},
        {'0', '1', '0'}
    };
    cout << sol.maximalRectangle(m) << endl;

    vector<vector<char>> m2 {
        {'0', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'},
        {'0', '1', '0'}
    };
    cout << sol.maximalRectangle(m2) << endl;

    vector<vector<char>> m3 {
        {'0', '1'}, 
        {'1', '0'}
    };
    cout << sol.maximalRectangle(m3) << endl;
    return 0;
}
