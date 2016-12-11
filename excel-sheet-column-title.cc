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
#include <sstream>

using namespace std;

class Solution {
    public:
        string convertToTitle(int n) {
            char s[11] = {'\0'};
            int i = 9;
            do {
                int r = (n-1) % 26;
                s[i--] = 'A'+r;
                n = (n-1) / 26;
            } while (n);

            return string(&s[i+1]);
        }
};

class Solution2 {
    public:
        string convertToTitle(int n) {
            string s;
            do {
                int r = (n-1) % 26;
                s.insert(s.begin(), 'A'+r);
                n = (n-1) / 26;
            } while (n);

            return s;
        }
};

int main(int argc, char *argv[])
{
    cout << Solution().convertToTitle(1) << endl;
    cout << Solution().convertToTitle(5) << endl;
    cout << Solution().convertToTitle(26) << endl;
    cout << Solution().convertToTitle(27) << endl; //aa
    cout << Solution().convertToTitle(52) << endl; //az
    cout << Solution().convertToTitle(53) << endl; //ba
    cout << Solution().convertToTitle(728) << endl; //aaa
    
    return 0;
}
