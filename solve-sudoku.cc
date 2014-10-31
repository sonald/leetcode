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

class Solution2 {
public:
    bool rows_state[9][9];
    bool cols_state[9][9];
    bool grid_state[9][9];

    void solveSudoku(vector<vector<char> > &board) {
        memset(rows_state, false, sizeof rows_state);
        memset(cols_state, false, sizeof cols_state);
        memset(grid_state, false, sizeof grid_state);                

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int k = board[i][j] - '1', gd = (i/3)*3+j/3;
                rows_state[i][k] = cols_state[j][k] = true;
                grid_state[gd][k] = true;
            }
        }
        solverIt(board, 0);
    }

    bool solverIt(vector<vector<char> > &board, int id) {
        int i = id / 9, j = id % 9;
        while (board[i][j] != '.') {
            if (id == 80) return true;
            id++;
            i = id / 9, j = id % 9;
        }

        for (int c = '1'; c <= '9'; c++) {
            int k = c - '1', gd = (i/3)*3+j/3;
            if (rows_state[i][k] || cols_state[j][k] || grid_state[gd][k]) 
                continue;

            rows_state[i][k] = cols_state[j][k] = grid_state[gd][k] = true;

            board[i][j] = c;
            if (id == 80) return true;
            if (solverIt(board, id+1)) {
                return true;
            }
            rows_state[i][k] = cols_state[j][k] = grid_state[gd][k] = false;
            board[i][j] = '.';
        }
        return false;
    }
};

//backtracking
class Solution {
public:
    vector<vector<set<int>>> cached {9, vector<set<int>>(9)};
    void solveSudoku(vector<vector<char> > &board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.')
                    cached[i][j] = collectCandidates(board, i, j);
            }
        }

        solverIt(board, 0);
    }

    bool solverIt(vector<vector<char> > &board, int id) {
        int i = id / 9, j = id % 9;
        while (board[i][j] != '.') {
            if (id == 80) return true;
            id++;
            i = id / 9, j = id % 9;
        }
        int ch = board[i][j];

        auto cand = cached[i][j];
        postprocess(cand, board, i, j);
        for (int c: cand) {
            board[i][j] = c;
            if (id == 80) return true;
            if (solverIt(board, id+1)) {
                return true;
            }
            board[i][j] = '.';
        }
        return false;
    }

    // adjsut candidates 
    void postprocess(std::set<int>& v, vector<vector<char>>& board, int row, int col) {
        for (int j = 0; j < col; j++) {
            int ch = board[row][j];
            auto p = v.find(ch);
            if (p != v.end()) v.erase(p);
        }

        for (int i = 0; i < row; ++i) {
            int ch = board[i][col];
            auto p = v.find(ch);
            if (p != v.end()) v.erase(p);
        }

        int r = row/3, c = col/3;
        for (int i = 0; i < (row%3); i++) {
            for (int j = 0; j < (row%3); j++) {
                int ch = board[r*3+i][c*3+j];
                auto p = v.find(ch);
                if (p != v.end()) v.erase(p);
            }
        }
    }

    std::set<int> collectCandidates(vector<vector<char> > &board, int row, int col) {
        std::set<int> res;
        unordered_map<int, bool> has;
        for (int j = 0; j < 9; j++) {
            int ch = board[row][j];
            if (has[ch]) continue;
            if (ch != '.')
                has[ch] = true;
        }

        for (int i = 0; i < 9; ++i) {
            int ch = board[i][col];
            if (has[ch]) continue;
            if (ch != '.')
                has[ch] = true;
        }

        int r = row/3, c = col/3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int ch = board[r*3+i][c*3+j];
                if (has[ch]) continue;
                if (ch != '.')
                    has[ch] = true;
            }
        }

        for (int c = '1'; c <= '9'; c++) {
            if (!has[c]) res.insert(c);
        }

        return res;
    }

};

void test(vector<vector<char> > &board) {
	Solution2().solveSudoku(board);
    cout << board << endl;
}

int main(int argc, char const *argv[])
{
	{
        std::vector<std::vector<char> > v {
			{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
			{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
			{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
			{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
			{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
			{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
			{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
			{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
			{'.', '.', '.', '.', '8', '.', '.', '7', '9'},
		};
		test(v);
	}
	
    {
        std::vector<std::vector<char> > v {   
            {'.', '.', '.', '.', '.', '7', '.', '.', '9'},
            {'.', '4', '.', '.', '8', '1', '2', '.', '.'},
            {'.', '.', '.', '9', '.', '.', '.', '1', '.'},
            {'.', '.', '5', '3', '.', '.', '.', '7', '2'},
            {'2', '9', '3', '.', '.', '.', '.', '5', '.'},
            {'.', '.', '.', '.', '.', '5', '3', '.', '.'},             
            {'8', '.', '.', '.', '2', '3', '.', '.', '.'},
            {'7', '.', '.', '.', '5', '.', '.', '4', '.'},
            {'5', '3', '1', '.', '7', '.', '.', '.', '.'},
        };
        test(v);
    }
	return 0;
}