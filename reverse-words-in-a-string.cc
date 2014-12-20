#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        void reverseWords(string &s) {
            auto i = std::find_if_not(s.begin(), s.end(), std::isblank);
            s.erase(s.begin(), i);

            auto ss = s;
            i = s.begin();
            while (i != s.end()) {
                auto j = std::find_if(i, s.end(), std::isblank);
                auto l = j;
                j--;
                while (i < j) {
                    std::iter_swap(i, j);
                    i++; j--;
                }
                i = l;
                while (i != s.end() && std::isblank(*next(i))) {
                    i = s.erase(i);
                }
                if (i != s.end()) i++;
            }

            while (s.size()) {
                if (isblank(s[s.size()-1])) s.erase(s.size()-1);
                else break;
            }

            std::reverse(s.begin(), s.end());
        }
};

void test(string s) {
    Solution().reverseWords(s);
    cout <<"|" << s <<"|" << endl;
}

int main(int argc, char *argv[])
{
    test("   hello     world is  ok? ");
    test("    ");
    test("  aabb   ");
    test("a");
    return 0;
}
