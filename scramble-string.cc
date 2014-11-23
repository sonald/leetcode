#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
    os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]";
}


template<class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	bool f = true;
	os << "{";
    for (auto& t: v) {
    	if (f) os << "(" << t.first << "," << t.second << ")";
    	else os << "," << "(" << t.first << "," << t.second << ")";
    }
    return os << "}";
}

// DP way
class Solution2 {
public:
    std::vector<vector<vector<int>>> dp;

    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        int n = s1.size();
        if (n == 0) return true;

        dp = vector<vector<vector<int>>>(n, 
            vector<vector<int>>(n, vector<int>(n, 0)));
        return scramble(s1, 0, n-1, s2, 0);
    }

    inline bool match(string& s1, int i, int j, string& s2, int p) {
        // cout << "match " << s1.substr(i, j-i+1) << ", " << s2.substr(p, j-i+1) << endl;
        return std::equal(s1.begin()+i, s1.begin()+j+1, s2.begin()+p);
    }

    bool scramble(string& s1, int i, int j, string& s2, int p) {
        auto& x = dp[i][j];
        if (x[p] == 1) return true;
        else if (x[p] == 2) return false;
        
        if (match(s1, i, j, s2, p)) {
            x[p] = 1;
            return true;
        }

        for (int k = i+1; k <= j; k++) {
            if (scramble(s1, i, k-1, s2, p) && scramble(s1, k, j, s2, p+k-i)) {
                x[p] = 1;
                return true;
            }

            if (scramble(s1, k, j, s2, p) && scramble(s1, i, k-1, s2, p+j-k+1)) {
                x[p] = 1;
                return true;
            }
        }

        x[p] = 2;
        return false;
    }
};


// smart idea: seq merging (bottom-up way)
// but.... slow P(s1.size()) would be huge
class Solution {
public:
    unordered_map<char, vector<int>> h;
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        int n = s1.size();
        if (n == 0) return true;

        unordered_map<char, int> use;
        for (int i = 0; i < n; i++) {
            h[s1[i]].push_back(i);
        }
        // cout << "h " << h << endl;

        auto hp = h.begin();
        while (hp != h.end()) {            
            for (auto& x: h) use[x.first] = 0; // last usable id in h[s1[i]]

            std::vector<vector<int>> seq(n);
            for (int i = 0; i < n; i++) {
                auto ch = s2[i];
                if (use.find(ch) == use.end()) return false;         
                auto& p = h[ch];                
                seq[i] = {p[use[ch]++]};
            }
            // cout << "seq " << seq << endl;

            if (isRestorable(s1, seq)) return true;

            while (hp != h.end() && hp->second.size() == 1) hp++;            
            if (hp != h.end() && !next_permutation(hp->second.begin(), hp->second.end())) {
                hp++;
                while (hp != h.end() && hp->second.size() == 1) hp++;            
            }            
        }
        return false;
    }

    bool isRestorable(string& s1, vector<vector<int>>& seq) {
        while (seq.size() > 1) {
            int sz = seq.size();
            auto i = seq.begin() + 1;
            while (i != seq.end()) {
                auto& v = *i;
                auto& pre = *(i-1);
                if (abs(v.front() - pre.back()) == 1
                    || abs(v.back() - pre.front()) == 1 ) {
                    if (v.front() > pre.back())
                        pre.insert(pre.end(), v.begin(), v.end());
                    else 
                        pre.insert(pre.begin(), v.begin(), v.end());
                    i = seq.erase(i);
                } else i++;
            }
            // cout << "up " << seq << endl;
            if (sz == seq.size()) return false; // can not merge
        }

        return true;
    }
};


void test(const string& s, const string& k) {
    cout << Solution().isScramble(s, k) << " ";    
    // cout << Solution().isScramble(s, k) << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    test("aabc", "baca"); //1
    // return 0;
    test("great", "rgtae"); // 1
    test("", ""); // 1 
    test("abcd", "dcba"); // 1
    test("abcd", "dabc"); //1
    test("abcd", "bcad"); // 1

    test("abcde", "caebd"); // 0    
    test("abcd", "bdac"); //0
    test("a", "b"); // 0

    test("ccabcbabcbabbbbcbb", "bbbbabccccbbbabcba");
    return 0;   
}