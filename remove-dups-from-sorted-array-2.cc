#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int res = n, i = n-1;
        while (i >= 0) {
            int k = 0;
            while (i >= 1 && A[i-1] == A[i]) {
                k++; i--;
            }
            if (k > 1) {
                memmove(A+i, A+i+k-1, sizeof(int)*(n-i-k+1));
                res -= k-1;
            } else i--;
        }
        return res;
    }
};

void test(int A[], int n)
{
    Solution sol;
    int k = sol.removeDuplicates(A, n);
    cout << k << ": ";
    for (int i = 0; i < k; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}


int main(int argc, char *argv[])
{
    {
        int A[] = {1, 1, 1, 1};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n);
    }
    {
        int A[] = {1};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n);
    }
    {
        int A[] = {1, 2};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n);
    }
    {
        int A[] = {1, 1, 2, 4, 4, 4, 5, 8, 9, 9};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n);
    }
    {
        int A[] = {1, 1, 2};
        int n = 3;
        test(A, n);
    }
    {
        int A[] = {1, 1, 1, 2, 2, 3};
        int n = 6;
        test(A, n);
    }
    return 0;
}




