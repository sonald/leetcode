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
        using part = vector<string>;
        inline bool ispal(const string& s) {
            for (int i = 0, sz = s.size(), j = sz-1; i <= j; i++, j--) {
                if (s.at(i) != s.at(j)) return false;
            }

            return true;
        }

        //incredibly slow
        vector<vector<string>> partition(string s) {
            //cout << "partition: " << s << endl;
            vector<part> parts;
            const char* cs = s.data();
            auto sz = s.size();

            if (sz == 0) return {{}};
            else if (sz == 1) { return {{s}}; }

            auto sub = partition(s.substr(0, sz-1));
            bool mark = false;
            for (auto& p: sub) {
                //cout << p << endl;
                string ss;
                p.push_back({cs[sz-1]});
                do {
                    string tmp = p.at(p.size()-1);
                    p.pop_back();
                    ss = tmp + ss;
                    if (ispal(ss)) {
                        if (p.size() == 0) {
                            if (mark) break;
                            mark = true;
                        }
                        part pp = p;
                        pp.push_back(ss);
                        parts.push_back(pp);
                    }

                } while (p.size());
            }
            return parts;
        }

        static constexpr int N {1000};
        vector<vector<string>> partition2(string s) {
            vector<part> parts;

            const char* cs = s.data();
            int rs = 0, rl = 1;
            int dp[N][N] {{0}};
            auto sz = s.size();
            for (int i = 0; i < sz; ++i) {
                dp[i][i] = 1;
            }

            for (int i = 0; i < sz-1; ++i) {
                if (cs[i] == cs[i+1]) {
                    rs = i; 
                    rl = 2;
                    dp[i][i+1] = 2;
                }
            }

            for (int l = 2; l < sz; ++l) {
                for (int i = 0; i < sz-l; ++i) {
                    auto& p = dp[i][i+l];
                    p = 0;
                    if ((cs[i] == cs[i+l]) && dp[i+1][i+l-1]) {
                        p = dp[i+1][i+l-1] + 2;
                    }
                    if (p > rl) {
                        rl = p;
                        rs = i;
                    }
                }
            }

            for (int l = 0; l < sz; ++l) {
                part pp;
                int p = 0, j = l, m = 0;
                while (j < sz) {
                    if (dp[p][j]) {
                        pp.push_back(s.substr(p, dp[p][j]));
                        m += dp[p][j];
                        p = ++j;
                    } else {
                        ++j;
                    }
                }
                if (m == sz) parts.push_back(pp);
            }
            return helper(s, 0, dp);
        }

        vector<vector<string>> helper(const string& s, int p, int dp[N][N]) {
            vector<part> parts;
            auto sz = s.size();
            for (int l = 0; l + p < sz; ++l) {
                if (dp[p][p+l]) {
                    if (p+l == sz-1) {
                        parts.push_back({s.substr(p, l+1)});
                        continue;
                    }

                    auto sub = helper(s, p+l+1, dp);
                    for (auto& x: sub) {
                        part pp;
                        pp.push_back(s.substr(p, l+1));
                        copy(x.begin(), x.end(), back_inserter(pp));
                        parts.push_back(pp);
                    }
                }
            }

            return parts;
        }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << sol.partition2("aa") << endl;    
    cout << sol.partition2("a") << endl;    
    cout << sol.partition2("aab") << endl;    
    cout << sol.partition2("aabaa") << endl;    
    cout << sol.partition2("seeslaveidemonstrateyetartsnomedieva") << endl;    
    cout << sol.partition2("seeslaveidemonstrateyetartsnomedievalsees") << endl;    

    return 0;
}
