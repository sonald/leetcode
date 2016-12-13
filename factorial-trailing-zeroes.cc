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

using namespace std;

class Solution {
public:
    // f(5^d) = 5^d/5 + 5^(d-1)/5 + .... + 5^1/5
    int trailingZeroes(int n) {
        int res = 0;
        while (n) {
            n /= 5;
            res += n;
        }

        return res;
    }
};

int main(int argc, char *argv[])
{
    
    cout << Solution().trailingZeroes(2) << endl; // 0
    cout << Solution().trailingZeroes(5) << endl; // 1
    cout << Solution().trailingZeroes(9) << endl; // 1
    cout << Solution().trailingZeroes(10) << endl; // 2
    cout << Solution().trailingZeroes(15) << endl;  // 3
    cout << Solution().trailingZeroes(21) << endl;  // 4
    cout << Solution().trailingZeroes(25) << endl;  // 6
    cout << Solution().trailingZeroes(125) << endl; // 31
    cout << Solution().trailingZeroes(130) << endl; // 32
    return 0;
}
