#include <iostream>
#include <cassert>
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
        int removeElement(int A[], int n, int elem) {
            int i = 0, j = n-1;
            int c = 0;
            while (i <= j) {
                if (A[i] != elem) {
                    i++; 
                    continue;
                }

                c++;
                while (j > i && A[j] == elem) {
                    j--;
                    c++;
                }

                if (j <= i) break;
                assert(A[i] == elem);
                A[i] = A[j];
                A[j] = elem;
                j--;
            }
            
            if (n == 1 && A[0] == elem) return 0;
            return n-c;
        }
};

void test(int A[], int n, int elem) 
{
    Solution sol;
    cout << sol.removeElement(A, n, elem) << endl;
    for (int i = 0; i < n; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    {
        int A[] = {1, 2, 4, 8, 4, 9, 6, 4};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n, 4);
    }
    {
        int A[] = {1, 2, 4, 8, 4, 9, 6, 4};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n, 1);
    }
    {
        int A[] = {1};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n, 1);
    }
    {
        int A[] = {1, 1};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n, 1);
    }
    {
        int A[] = {4, 5};
        int n = sizeof(A)/sizeof(A[0]);
        test(A, n, 5);
    }
    return 0;
}






