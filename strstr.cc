#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        char *strStr(char *haystack, char *needle) {
            if (!*needle) return haystack;
            if (!needle) return NULL;
            int m = strlen(needle);

            while (*(haystack+m-1)) {
                char* p = haystack;
                const char* t = needle;
                while (*p && *t && *p == *t) 
                    p++, t++;
                if (*t == 0) 
                    return haystack;
                
                
                haystack++;
            }

            return NULL;
        }
};

void test(char *haystack, char *needle)
{
    Solution sol;
    char* p = sol.strStr(haystack, needle);
    cout << (p?p:"(NULL)") << endl;
}

int main(int argc, char *argv[])
{
    test("hello", "llo");
    test("hello", "hllo");
    test("aaaaaaaaab", "aaaaaaac");
    test("", "");
    test("b", "");
    return 0;
}

