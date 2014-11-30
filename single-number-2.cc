#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
    public:
        int singleNumber(int A[], int n) {
            int ones = 0, twos = 0;
            for(int i = 0; i < n; i++){
                ones = (ones ^ A[i]) & ~twos;
                twos = (twos ^ A[i]) & ~ones;
            }
            return ones;
        }
};

int main(int argc, char *argv[])
{
    {
        int a[] = {7, 2, 7, 123, 2, 7, 2};
        cout << Solution().singleNumber(a, 7) << endl; // 123
    }
    return 0;
}




