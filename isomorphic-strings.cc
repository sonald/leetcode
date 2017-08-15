#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution2 {
public:
    bool isIsomorphic(string s, string t) {
        char m[256] = {0, };
        bool mapped[256] = {false, };

        for (int i = 0; i < s.size(); ++i) {
            int c = s[i], c2 = t[i];
            if (m[c] != 0) {
                if (m[c] != c2) {
                    return false;
                }
            } else {
                m[c] = c2;
                if (mapped[c2]) return false;
                mapped[c2] = true;
            }
        }

        return true;
    }
};

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int m1[256] = {0, }, m2[256] = {0, }, n = s.size();

        for (int i = 0; i < n; i++) {
            int sv = s[i], tv = t[i];
            if (m1[sv] != m2[tv]) return false;
            m1[sv] = i+1;
            m2[tv] = i+1;
        }

        return true;
    }
};

static void test(string s, string t, bool expect) 
{
    //auto b = Solution2().isIsomorphic(s, t);
    auto b = Solution().isIsomorphic(s, t);
    //assert(b == expect);
    cout << s << ", " << t << "=" << b << endl;
}

int main(int argc, char *argv[])
{
    test("egg", "add", true); 
    test("paper", "title", true); 
    test("foo", "bar", false); 
    test("paper", "titlt", false); 
    return 0;
}
