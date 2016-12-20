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
    bool isPowerOfTwo(int n) {
        return n > 0 &&  !(n & (n-1));
    }
};

int main(int argc, char *argv[])
{
    
    cout << Solution().isPowerOfTwo(0) << endl; 
    cout << Solution().isPowerOfTwo(1) << endl; 
    cout << Solution().isPowerOfTwo(3) << endl; 
    cout << Solution().isPowerOfTwo(8) << endl; 
    cout << Solution().isPowerOfTwo(9) << endl; 
    cout << Solution().isPowerOfTwo(12) << endl; 
    return 0;
}
