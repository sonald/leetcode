#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
    public:
        void merge(int A[], int m, int B[], int n) {
            int i = m-1, j = n-1;
            int *p = A + m + n - 1;
            while (i >= 0 && j >= 0) {
                if (A[i] > B[j]) {
                    *p-- = A[i--];
                } else {
                    *p-- = B[j--];
                }
            }

            while (j >= 0) {
                *p-- = B[j--];
            }            
        }
};

void test(int A[], int m, int B[], int n) 
{
    Solution().merge(A, m, B, n);
    for (int i = 0; i < m+n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    int a[1] = {};
    int b[] = {1};
    test(a, 0, b, 1);

    int a1[3] = {3, 5};
    int b1[] = {2};
    test(a1, 2, b1, 1);

    int a2[4] = {3, 5};
    int b2[] = {2, 7};
    test(a2, 2, b2, 2);

    int a3[3] = {};
    int b3[] = {2, 3};
    test(a3, 0, b3, 2);
    return 0;
}
