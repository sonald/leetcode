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
    os << "[\n";
    for (const auto& t: v) {
        os << t << "\n";
    }
    return os << "]\n";
}

class Solution {
public:
    std::vector<bool> cols;
    std::vector<bool> diags;
    std::vector<bool> rdiags;

    int totalNQueens(int n) {
        cols = std::vector<bool>(n, false);
        diags = std::vector<bool>(n, false);
        rdiags = std::vector<bool>(n, false);

        int res = 0;
        if (n <= 0) return 0;

        std::vector<string> ans(n, string(n, '.'));
        solve(res, ans, n, 0);
        return res;
    }

    void solve(int& res, vector<string>& board, int n, int row) {
        if (row == n) {
            res++;
            return;
        }

        for (int i = 0; i < n; i++) {
            int d = row + i, rd = n - 1 - row + i;
            if (!cols[i] && !diags[d] && !rdiags[rd]) {
                board[row][i] = 'Q';
                cols[i] = diags[d] = rdiags[rd] = true;
                solve(res, board, n, row+1);
                cols[i] = diags[d] = rdiags[rd] = false;
                board[row][i] = '.';
            }
        }
    }
};


void test(int n) {
    cout << n << ": " << Solution().totalNQueens(n) << endl;    
}

int main(int argc, char const *argv[])
{
    // test(13);
    for (int i = 0; i < 9; i++)
        test(i);
    return 0;
}