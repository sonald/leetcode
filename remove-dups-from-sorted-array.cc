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
        int removeDuplicates2(int A[], int n) {
            int k = n;
            for (int i = n-1; i > 0; --i) {
                int t = i, p = A[i];
                while (t > 0 && p == A[t-1]) { t--; }
                if (t != i) {
                    memmove(&A[t], &A[i], sizeof(int)*(k-i));
                    k -= i - t;
                    i = t + 1;
                }
            }
            return k;
        }

        int removeDuplicates(int A[], int n) {
            int k = n, sentinal = A[n-1] + 1;
            for (int i = n-1; i > 0; --i) {
                int t = i, p = A[i];
                while (t > 0 && p == A[t-1]) {
                    A[t-1] = sentinal;
                    t--; 
                }
                if (t != i) {
                    k -= i - t;
                    i = t + 1;
                }
            }
            
            for (int i = 0, j = 0; i < n;) {
                while (j < n && A[j] != sentinal) j++;
                if (i<j) i = j;
                while (i < n && A[i] == sentinal) i++;
                if (j >= n || i >= n) break;
                A[j] = A[i];
                A[i] = sentinal;
                ++i;
                ++j;
            }
            return k;
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
    return 0;
}




