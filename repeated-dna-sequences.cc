#include <iostream>
#include <sstream>
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

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (auto& s: v) {
        os << s << ", ";
    }
    return os << "]";
}

#define VER 2

#if VER == 1
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;

        unordered_map<string, int> occurs;
        for (int i = 0, n = s.size(); i + 9 < n; i++) {
            string t = s.substr(i, 10);
            occurs[t]++;
        }

        for (auto& t: occurs) {
            if (t.second > 1)
                res.emplace_back(t.first);
        }
        return res;
    }
};
#else
// A-0, C-1, G-2, T-3
#define BITVAL(ch) ((ch) == 'A' ? 0: (ch) == 'C' ? 1 : (ch) == 'G' ? 2 : 3)
#define BITCHAR(v) ((v) == 0 ? 'A': (v) == 1 ? 'C' : (v) == 2 ? 'G' : 'T')
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;

        if (s.size() < 10) return res;
        
        // unordered_map is relatively slow compare to this static map 
        // considering there are only at most 1<<20 possibilities
        int occurs[1<<20] = {0};

        unsigned seq = BITVAL(s[0]);
        for (int i = 1; i < 10; i++) {
            seq <<= 2;
            seq |= BITVAL(s[i]);
        }

        occurs[seq]++;
        for (int i = 10, n = s.size(); i < n; i++) {
            seq &= 0x3ffff;
            seq <<= 2;
            seq |= BITVAL(s[i]);
            if (occurs[seq] == 1) {
                res.emplace_back(seq2str(seq));
            }
            occurs[seq]++;
        }

        return res;
    }

    string seq2str(unsigned seq) {
        string t(10, '\0');
        for (int i = 0; i < 10; i++) {
            t[9-i] = BITCHAR(seq&3);
            seq >>= 2;
        }
        return t;
    }
};
#endif

int main(int argc, char *argv[])
{
    /*
     * Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
     * Return: ["AAAAACCCCC", "CCCCCAAAAA"].
     */

    cout << Solution().findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT") << endl;
    cout << Solution().findRepeatedDnaSequences("AAAAAAAAAAA") << endl;
    cout << Solution().findRepeatedDnaSequences("AAAAAAAAAAAA") << endl;
    cout << Solution().findRepeatedDnaSequences("AAAAA") << endl;

    return 0;
}


