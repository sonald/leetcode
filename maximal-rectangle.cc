#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;
ostream& operator<<(ostream& os, pair<int, int> v)
{
    return os << "(" << v.first << "," << v.second << ")";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    ::for_each(v.begin(), v.end(), [&](const T& t) { 
        os << t;
    });
    return os << "]" << endl;
}

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int max = 0;

        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int rows = matrix.size(), cols = matrix[0].size();

        //augmented
        vector<vector<int>> collect(rows+1, vector<int>(cols+1, 0));

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if (matrix[i-1][j-1] == '1') {
                    collect[i][j] = collect[i-1][j] + 1;
                }
            }
        }

        // cout << "collect: \n" << collect << endl;
        for (int i = 1; i <= rows; ++i) {
             std::vector<pair<int, int>> sp; // <high, index>
             sp.emplace_back(0, 0);
             for (int j = 1; j <= cols; j++) {
                int k = collect[i][j];
                while (sp.size() && sp.back().first >= k) {
                    sp.pop_back();
                }
                sp.emplace_back(k, j);

                // cout << "(i, j) = " << i << "," << j << ", sp: " << sp << endl;
                for (int p = 1; p < sp.size(); p++) {
                    auto h = sp[p].first;
                    auto w = j - sp[p-1].second;
                    if (max < w * h) {
                        max = w * h;
                        // cout << "max -> " << max << endl;
                    }
                }
            }
        } 
        return max;
    }

};

void test(vector<vector<char> > matrix) {
    cout << Solution().maximalRectangle(matrix) << endl;
}

int main(int argc, char *argv[])
{
    vector<vector<char>> m4 {
        {'0', '0', '0', '1', '0'},
        {'1', '0', '1', '1', '0'},
        {'1', '1', '0', '1', '1'},
        {'1', '1', '1', '1', '0'},
        {'0', '1', '1', '1', '0'}
    };
    test(m4); // 6

    vector<vector<char>> m {
        {'1', '1', '0'},
        {'1', '1', '0'},
        {'1', '0', '0'},
        {'0', '1', '0'}
    };
    test(m); // 4

    vector<vector<char>> m2 {
        {'0', '0', '1'},
        {'0', '1', '0'},
        {'1', '1', '1'},
        {'0', '1', '0'}
    };
    test(m2); // 3

    vector<vector<char>> m3 {
        {'0', '1'}, 
        {'1', '0'}
    };
    test(m3); // 1

    {
        std::vector<std::vector<char>> v;
        test(v);
    }
    return 0;
}
