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
    int titleToNumber(string s) {
        int d = 0;
        int r = 1;
        for (int i = 0, j = s.size()-1; j >= 0; i++, j--) {
            d += (s[j] - 'A' + 1) * r;
            r *= 26;
        }

        return d;
    }
};

int main(int argc, char *argv[])
{
    cout << Solution().titleToNumber("A") << endl;
    cout << Solution().titleToNumber("E") << endl;
    cout << Solution().titleToNumber("Z") << endl;
    cout << Solution().titleToNumber("AA") << endl;
    cout << Solution().titleToNumber("AZ") << endl;
    cout << Solution().titleToNumber("BA") << endl;
    cout << Solution().titleToNumber("AAZ") << endl;
    return 0;
}

