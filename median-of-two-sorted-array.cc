#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution3 {
    public:
        double median(int A[], int m, int B[], int n, int k) {
            // cout << "m " << m << ", n " << n << ", k " << k << endl;
            if (m == 0) return B[k];
            else if (n == 0) return A[k];
            if (k == 0) return min(A[0], B[0]);

            int ka = min((k)/2, m-1), kb = k - ka - 1;
            // cout << "ka " << ka << ", kb " << kb << endl;
            if (kb < 0) return A[ka];
            else if (kb > n-1) { kb = n-1; ka = k - kb - 1; }

            int va = A[ka], vb = B[kb];
            if (A[ka] >= B[kb]) return median(A, m, B+kb+1, n-kb-1, k-kb-1);
            else return median(A+ka+1, m-ka-1, B, n, k-ka-1);
        }

        double findMedianSortedArrays(int A[], int m, int B[], int n) {
            auto mid = (m+n-1)/2;
            bool even = (m+n)%2 == 0;

            if (even) 
                return (median(A, m, B, n, mid) + median(A, m, B, n, mid+1))/2.0;
            else 
                return median(A, m, B, n, mid);
        }
};

class Solution2 {
    public:
        // find right most index whose value is equal or less than val, or -1
        int after(int* arr, int len, int val) {
            int l = 0, r = len-1, m = l;
            while (l <= r) {
                m = l + (r-l)/2;
                if (arr[m] == val) return m;
                else if (arr[m] > val) r = m-1;
                else l = m+1;
            }
            if (arr[m] > val) m--;
            return m;
        }

        double single(int* arr, int len, bool even, int mid) {
            double res = arr[mid];
            if (even) res = (res + arr[mid+1]) / 2.0; 
            return res;
        }

        double findMedianSortedArrays(int A[], int m, int B[], int n) {
            auto mid = (m+n-1)/2;
            bool even = (m+n)%2 == 0;
            if (m == 0) return single(B, n, even, mid);
            else if (n == 0) return single(A, m, even, mid);

            int *pa = A, *pb = B;
            if (A[0] > B[0]) { pa = B, pb = A; std::swap(m, n); }

            double res = 0.0; 

            // treat pa as buckets, and pb are values split into buckets
            // first find which bucket mid reside in, then locate it in the bucket

            // find bucket
            int l = 0, r = m-1, gid = -1, k = l;
            while (l <= r) {
                k = l + (r-l)/2;
                gid = after(pb, n, pa[k]) + k + 1;
                if (mid == gid) {
                    res = pa[k];
                    if (even) {
                        int t = gid - k;
                        if (t >= 0 && pb[t] < pa[k+1]) 
                            res += pb[t];
                        else res += pa[k+1];
                        res /= 2.0;
                    }
                    return res;
                } else if (mid < gid) {
                    r = k-1;
                } else l = k+1;
            }

            if (gid >= mid) k--;
            mid -= k+1;
            res = pb[mid];
            if (even) {
                if (mid + 1 == n || (k+1 < m && pa[k+1] < pb[mid+1])) res += pa[k+1];
                else res += pb[mid+1];
                res /= 2.0;
            }

            return res;
        }
};

//O(m+n)
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

void test(int A[], int m, int B[], int n) 
{
    cout << Solution().findMedianSortedArrays(A, m, B, n) << endl;
    cout << Solution2().findMedianSortedArrays(A, m, B, n) << endl;
    cout << Solution3().findMedianSortedArrays(A, m, B, n) << endl;
    cout << "--------------\n";
}

#define LEN(a) (sizeof (a) /sizeof(a[0]))

int main(int argc, char *argv[])
{
    int a[] = {};
    int b[] = {1};
    test(a, 0, b, 1);

    int a1[] = {3, 5};
    int b1[] = {2};
    test(a1, 2, b1, 1);

    int a2[] = {3, 5};
    int b2[] = {2, 7};
    test(a2, 2, b2, 2);

    int a3[] = {};
    int b3[] = {2, 3};
    test(a3, 0, b3, 2);

    {
        int a[] = {2,3,4,5,6,7};
        int b[] = {1};
        test(a, LEN(a), b, LEN(b));
    }
    {
        int a[] = {2};
        int b[] = {1,3,4};
        test(a, LEN(a), b, LEN(b));
    }

    {
        int a[] = {1,3,4,8,9};
        int b[] = {2,5,5,6,7,18};
        test(a, LEN(a), b, LEN(b));
    }

    {
        int a[] = {1,3,4,8,9,15};
        int b[] = {2,5,5,6,7,18};
        test(a, LEN(a), b, LEN(b));
    }

    {
        int a[] = {1,2,4,8,9,15};
        int b[] = {3,4,5,6,7,18};
        test(a, LEN(a), b, LEN(b));
    }
    {
        int a[] = {1, 12, 15, 26, 38};
        int b[] = {2, 13, 17, 30, 45, 50};
        test(a, LEN(a), b, LEN(b));
    }
    return 0;
}
