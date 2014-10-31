#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        int searchInsert(int A[], int n, int target) {
            int i = 0;
            for (; i < n; ++i) {
                if (target <= A[i]) 
                    break;
            }
            return i;
        }

};

void test(int A[], int n, int target)
{
    Solution sol;
    cout << sol.searchInsert(A, n, target) << endl;
}

int main(int argc, char *argv[])
{
    {
        int A[] = {1,3,5,6};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n, 5);
        test(A, n, 2);
        test(A, n, 7);
        test(A, n, 0);
    }    
    return 0;
}



