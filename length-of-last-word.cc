#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (const auto& t: v) {
        os << t << "  ";
    }
    return os << "]\n";
}

class Solution {
public:
    int lengthOfLastWord(const char *s) {
        if (s == NULL) return 0;
        int st = 0, res = 0;
        while (*s) {
            if (!st && *s != ' ') {
                st = 1; res = 1;
            } else if (st) {
                if (*s == ' ') {
                    st = 0; 
                } else res++;
            }
            s++;
        } 

        return res;
    }
};

void test(const char* s) {
    cout << Solution().lengthOfLastWord(s) << endl;
}

int main(int argc, char const *argv[])
{
    test(0);
    test("");
    test("  ");
    test("he ");
    test("    abc");
    test("  afds  ");
    test("helo world");
	return 0;
}