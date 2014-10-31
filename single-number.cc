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
            int r = 0;
            for (int i = 0; i < n; ++i) {
                r ^= A[i];
            }

            return r;
        }
};

int main(int argc, char *argv[])
{
    {
        int a[] = {1, 2, 4, 2, 3, 4, 1};
        cout << Solution().singleNumber(a, 7) << endl;
    }
    return 0;
}




