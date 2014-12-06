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
        bool isPalindrome(string s) {
            for (int i = 0, j = s.size()-1; i <= j;) {
                if (!std::isalnum(s[i])) { i++; }
                else if (!std::isalnum(s[j])) { j--; }
                else {
                    if (tolower(s[i]) != tolower(s[j])) return false;
                    i++, j--;
                }
            }
            return true;
        }
};

void test(string s) 
{
    cout << Solution().isPalindrome(s) << endl;
}
int main(int argc, char *argv[])
{
    test(""); // 1
    test("A man, a plan, a canal: Panama"); //1
    test("race a car"); // 0
    test("rac:   a car"); // 1
    return 0;
}
