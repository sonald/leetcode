#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

template<class T>
ostream& operator<<(ostream& os, const pair<T, T>& p)
{
    return os << "(" << p.first << "," << p.second << ")";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "(";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << x;
    }
    return os << ")";
}

class Solution {
    public:
        string convert(string s, int nRows) {
            if (nRows == 1) return s;

            vector<string> v(nRows);
    
            int iter = nRows*2-2, zag = 0;
            for (int i = 0, sz = s.size(); i < sz; ++i) {
                zag = (i%iter) >= nRows;
                int r = (i%iter) + (zag? zag-nRows: 0);
                r = zag?nRows-1-r: r; //reverse direction
                //cerr << "r: " << r << endl;
                v[r] += s[i];
            }

            string res;
            for (const auto& x: v) {
                res += x;
            }

            //cerr << res << endl;
            return res;
        }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << (sol.convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR") << endl;
    cout << sol.convert("PAYPALISHIRING", 4) << endl;
    cout << sol.convert("A", 1) << endl;
    cout << (sol.convert("ABCDE", 4) == "ABCED") << endl;
    return 0;
}
