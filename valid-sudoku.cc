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
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]";
}

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        for (int i = 0; i < 9; ++i) {
        	unordered_map<int, bool> has;
        	auto& row = board[i];
        	for (int j = 0; j < 9; j++) {
        		if (row[j] != '.' && has.find(row[j]) != has.end())
        			return false;
        		has[row[j]] = true;
        	}
        }

        for (int i = 0; i < 9; ++i) {
        	unordered_map<int, bool> has;
        	for (int j = 0; j < 9; j++) {
        		if (board[j][i] != '.' && has.find(board[j][i]) != has.end())
        			return false;
        		has[board[j][i]] = true;
        	}
        }

        for (int r = 0; r < 3; ++r) {
        	for (int c = 0; c < 3; c++) {
	        	unordered_map<int, bool> has;
	        	for (int i = 0; i < 3; i++) {
	        		for (int j = 0; j < 3; j++) {
	        			int ch = board[r*3+i][c*3+j];
	        			if (ch != '.' && has[ch])
	        				return false;
	        			has[ch] = true;
	        		}
	        	}
        	}
        }

        return true;
    }
};

void test(vector<vector<char> > &board) {
	cout << Solution().isValidSudoku(board) << endl;
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
	
	return 0;
}