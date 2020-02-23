#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const vector<string>& vs)
{
    for (auto& s: vs) {
        os << s << ",";
    }
    return os;
}


class Solution2 {
    public:
        vector<string> letterCombinations(string digits) {
            static unordered_map<char, string> m {
                {'1', ""},
                {'2', "abc"},
                {'3', "def"},
                {'4', "ghi"},
                {'5', "jkl"},
                {'6', "mno"},
                {'7', "pqrs"},
                {'8', "tuv"},
                {'9', "wxyz"},
                {'0', ""}
            };

            vector<string> vs {""};
            for (auto c: digits) {
                vector<string> vs2;
                for (const auto& s: vs) {
                    string r = m[c];
                    for (int i = 0, n = r.size(); i < n; ++i) 
                        vs2.push_back(s+r[i]);
                }
                vs = std::move(vs2);
            }

            return vs;
        }
};

class Solution {
    public:
        vector<string> letterCombinations(string digits) {
            static unordered_map<char, string> m {
                {'1', ""},
                {'2', "abc"},
                {'3', "def"},
                {'4', "ghi"},
                {'5', "jkl"},
                {'6', "mno"},
                {'7', "pqrs"},
                {'8', "tuv"},
                {'9', "wxyz"},
                {'0', ""}
            };

            vector<string> vs {""};
            return iterate(vs, digits, m);
        }

        vector<string> iterate(vector<string>& vs, string next,
                unordered_map<char, string>& m) {
            if (next.size() == 0) return vs;

            char c = next[0];
            vector<string> vs2;
            for (auto& s: vs) {
                string r = m[c];
                for (int i = 0, n = r.size(); i < n; ++i) 
                    vs2.push_back(s+r[i]);
            }
            
            return iterate(vs2, next.substr(1), m);
        }
};

class Solution3 {
    public:
        string res;
        unordered_map<char, string> m {
            {'1', ""},
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"},
            {'0', ""}
        };

        template<class UnaryFunction>
        void letterCombinations(string digits, UnaryFunction onGet) {
            res.resize(digits.size(), '\0');
            iterate(digits, 0, onGet);
        }

        template<class UnaryFunction>
        void iterate(const string& digits, int i, UnaryFunction onGet) {
            if (i == digits.size()) {
                onGet(res);
                return;
            }

            char j = digits[i];
            for (auto c: m[j]) {
                res[i] = c;
                iterate(digits, i+1, onGet);
            }
        }
};

void test(string s)
{
    Solution sol;
    cout << sol.letterCombinations(s) << endl;
}

int main(int argc, char *argv[])
{
    //test("23");
    //test("");
    //test("2");
    //cout << Solution().letterCombinations("942648744499").size() << endl;
    //cout << Solution3().letterCombinations("942648744499").size() << endl;
    Solution3().letterCombinations("99999999999", [](const string& s) {
        //cout << s << endl;
        s.size();
    });
    return 0;
}



