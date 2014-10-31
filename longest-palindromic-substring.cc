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

class Solution {
    public:
        using expect = pair<int, int>;
        static constexpr int N {1000};
        string preprocess(const string& s) {
            string ret;
            for_each(s.begin(), s.end(), [&ret](char c) { ret += string("#") + c; });
            return "^" + ret + "$";
        }

        //O(N)
        string longestPalindromeN1(string s) {
            string x = preprocess(s);
            string ret;
            int* p = new int[x.size()]{0};
            int C = 1, i = 1, R = 1;
            for (int n = x.size(); i < n; ++i) {
                if (R <= i) p[i] = 0;
                else p[i] = min(p[2*C-i], R-i);
                
                while (x[i+1+p[i]] == x[-1-p[i]])
                    p[i]++;

                if (p[i] > R - i) {
                    C = i;
                    R = p[i] + C;
                }
            }

            int len = 0, c = 0;
            for (int i = 1, n = x.size()-1; i < n; ++i) {
                if (p[i] > len) {
                    len = p[i];
                    c = i;
                }
            }

            delete[] p;

            return s.substr((c-1-len)/2, len);
        }

        //DP, O(n*n) time and space
        string longestPalindrome(string s) {
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

            return s.substr(rs, rl);
        }


        string expandFromCenter(const string& s, int c1, int c2) {
            int l = c1, r = c2, sz = s.size();
            for (; l >= 0 && r < sz && s[l] == s[r]; l--, r++) {
            }
            return s.substr(l+1, r-l-1);
        }

        // O(n*n) time, O(1) space
        string longestPalindrome3(string s) {
            int rs = 0, rl = 1;
            if (s.size() <= 1) return s;
            string res = s.substr(0, 1);

            for (int i = 0, sz = s.size(); i < sz-1; ++i) {
                string ss = expandFromCenter(s, i, i);
                if (ss.size() > rl) {
                    rl = ss.size(); rs = i - rl/2; 
                }

                ss = expandFromCenter(s, i, i+1);
                if (ss.size() > rl) {
                    rl = ss.size(); rs = i - rl/2 + 1; 
                }
            }

            return s.substr(rs, rl);
        }

        inline bool ispal(const string& s) {
            for (int i = 0, sz = s.size(), j = sz -1; i <= j; ++i, --j) {
                if (s[i] != s[j]) return false;
            }

            return true;
        }

        //brute force
        string longestPalindrome2(string s) {
            if (s.size() <= 1) return s;

            //2 outcomes, <start, len>
            expect e1 {0, 1}, e2 {0, 1};
            bool uniq = true;
            for (int i = 1, sz = s.size(); i < sz; ++i) {
                if (uniq) {
                    uniq = s[i] == s[0];
                }

                for (int j = 0; j < i; ++j) {
                    if (ispal(s.substr(j, i-j+1))) {
                        if (i-j+1 > e1.second) {
                            e1.first = j;
                            e1.second = i - j + 1;
                        }
                    }
                }

            }

            if (uniq) return s;
            return s.substr(e1.first, e1.second);
        }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << sol.longestPalindrome3("abcabd") << endl;
    cout << sol.longestPalindrome3("kbacabd") << endl;
    cout << sol.longestPalindrome3("m") << endl;
    cout << sol.longestPalindrome3("kk") << endl;
    cout << sol.longestPalindrome3("aakaadabbada") << endl;
    cout << sol.longestPalindrome3("ccc") << endl;
    cout << sol.longestPalindrome3("aaaa") << endl;

    string s{"aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa"};
    cout << (sol.longestPalindrome3(s).size() == s.size()) << endl;

    string s4{"civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth"};
    cout << (sol.longestPalindrome3(s4) == "ranynar") << endl;
    return 0;
}
