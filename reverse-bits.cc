#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ret = 0;

        uint32_t b = 0;
        while (n) {
            if (n & 1) {
                ret |= 1<<(31-b);
            }
            n >>= 1;
            b++;
        }

        return ret;
    }
};

int main(int argc, char *argv[])
{
    
    /* 43261596 (represented in binary as 00000010100101000001111010011100), 
     * 964176192 (represented in binary as 00111001011110000010100101000000).
     */

    cout << Solution().reverseBits(43261596) << endl;
    return 0;
}
