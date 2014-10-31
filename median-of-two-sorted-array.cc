#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
    public:
        double findMedianSortedArrays(int A[], int m, int B[], int n) {
            auto l = m + n, mid = (m+n)/2;
            double v = 0, w = 0;

            for (int i = 0, j = 0, k = 0; k <= l; ) {
                if (k == mid + 1) {
                    if (l % 2 == 0) {
                        return (w + v)/2.0;
                    } else 
                        return v;
                }

                w = v;
                if (i >= m) v = B[j++]; 
                else if (j >= n) v = A[i++];
                else if (A[i] > B[j]) v = B[j++];
                else v = A[i++];
                k++;
            }

            return 0;
        }
};

int main(int argc, char *argv[])
{
    int a[] = {};
    int b[] = {1};
    cout << Solution().findMedianSortedArrays(a, 0, b, 1) << endl;

    int a1[] = {3, 5};
    int b1[] = {2};
    cout << Solution().findMedianSortedArrays(a1, 2, b1, 1) << endl;

    int a2[] = {3, 5};
    int b2[] = {2, 7};
    cout << Solution().findMedianSortedArrays(a2, 2, b2, 2) << endl;

    int a3[] = {};
    int b3[] = {2, 3};
    cout << Solution().findMedianSortedArrays(a3, 0, b3, 2) << endl;
    return 0;
}
