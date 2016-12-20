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
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int c = 0;
        while (n) {
            if (n&1) c++;
            n >>= 1;
        }

        return c;
    }
};

class Solution2 {
public:
    int hammingWeight(uint32_t n) {
        int c = 0;
        while (n) {
            n &= n-1;
            c++;
        }

        return c;
    }
};

int main(int argc, char *argv[])
{
    int res[] = {
        0, 1, 1, 2, 1, 2, 2, 3, 
    };
    for (int i = 0; i < sizeof(res)/sizeof(res[0]); i++) {
        cout << Solution2().hammingWeight(i) << endl;
    }
    return 0;
}
