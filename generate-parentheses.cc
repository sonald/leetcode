#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const vector<string>& vs)
{
    for (const auto& s: vs) {
        os << s << ",";
    }
    return os;
}

class Solution {
    public:
        vector<string> generateParenthesis(int n) {
            set<string> vs;
            vector<string> sp;

            string o;
            for (int i = 0; i < n; ++i) o += "()";

            vs.insert(o);
            sp.push_back(o);
            while (sp.size()) {
                string s { sp.back() };
                sp.pop_back();
                for (int i = 0; i < n*2; ++i) {
                    if (s[i] == ')' && s[i+1] == '(') {
                        string s2 { swap(s, i, i+1) }; 
                        auto r = vs.insert(s2);
                        if (r.second) {
                            sp.push_back(s2);
                        }
                    }
                }
            }

            vector<string> ret;
            std::copy(vs.begin(), vs.end(), std::back_inserter(ret));
            return ret;
        }

        string swap(string s, int i, int j) {
            std::swap(s[i], s[j]);
            return s;
        }
};

void test(int n)
{
    Solution sol;
    cout << sol.generateParenthesis(n) << endl;
}

int main(int argc, char *argv[])
{
    test(3); //"((()))", "(()())", "(())()", "()(())", "()()()"
    test(6);
    
    return 0;
}


