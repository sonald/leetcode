#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        bool isValid(string s) {
            vector<char> sp {'#'};
            for (int i = 0, n = s.size(); i < n; ++i) {
                switch(s[i]) {
                    case '(':
                    case '{':
                    case '[':
                        sp.push_back(s[i]); break;

                    case ')': 
                        if (sp.back() != '(') return false;
                        sp.pop_back(); break;

                    case '}': 
                        if (sp.back() != '{') return false;
                        sp.pop_back(); break;

                    case ']': 
                        if (sp.back() != '[') return false;
                        sp.pop_back(); break;
                }
            }

            return sp.size() == 1;
        }
};

void test(string s)
{
    Solution sol;
    cout << sol.isValid(s) << endl;
}

int main(int argc, char *argv[])
{
    test("(){{}}");
    test("(()))(");
    test("[(])");  // = 0
    test("(");
    test("([])"); // = 1
    test("]");
   return 0;
}

