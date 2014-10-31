#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    public:
        bool isMatch(const char *s, const char *p) {
            if (!*s && !*p) return true;

            if (*p && *(p+1) == '*') {
                return matchStar(s, p);
            } else {
                return matchAny(s, p);
            }
        }

        bool matchStar(const char *s, const char *p) {
            const char pivot = *p, *sp = s;
            while (*sp && (pivot == '.' || pivot == *sp)) {
                sp++;
            }

            while (sp >= s) {
                if (!isMatch(sp, p+2)) {
                    --sp;
                } else 
                    return true;
            }
            return false;
        }

        bool matchAny(const char *s, const char *p) {
            if (*p && !*s) return false;
            if (!*p && *s) return false;

            if (*p == '.' || *s == *p) {
                return isMatch(++s, ++p);
            } else 
                return false;
        }
};

void test(const char *s, const char *p)
{
    Solution sol;
    cout << "(" << s << ", " << p << ")" << sol.isMatch(s, p) << endl;
}

int main(int argc, char *argv[])
{
    test("aa", "a");
    test("aa", "aa");
    test("aaa", "aa");
    test("aa", "a*");
    test("aa", ".*");
    test("ab", ".*");
    test("aab", "c*a*b");
    test("aaa", "a.a");
    test("aaa", "a*a");
    test("aaab", "a*a*");
    test("aaab", "a*a*b");
    test("a", "ab*");
    test("", "a*b*");
    test("", ".");
    test("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s");
    return 0;
}
