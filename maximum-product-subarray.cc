#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

// reduce the brute force way 
class Solution {
    public: 
        int maxProduct(int A[], int n) {
            int res = INT_MIN, cur = 1, rcur = 1;
            for (int i = 0; i < n; i++) {
                cur *= A[i], rcur *= A[n-i-1];
                res = max(res, max(cur, rcur));
                if (cur == 0) cur = 1;
                if (rcur == 0) rcur = 1;
            }
            return res;
        }
};

//brute force, non recursive
class Solution2 {
    public:
        int shrink(int A[], int n, int res, int l, int r, int s, int e) {
            if (s+1 >= e) return res;
            int lres = res, rres = res;
            if (l >= 0) {
                int v = res;
                for (int j = s; j <= l; j++) v /= A[j];
                lres = max(v, res);
            }

            if (r >= 0) {
                int v = res;
                for (int j = r; j < e; j++) v /= A[j];
                rres = max(v, res);
            }

            return res = max(lres, rres);
        }

        int maxProduct(int A[], int n) {
            if (n == 0) return 0;
            else if (n == 1) return A[0];

            bool haszero = false;
            int res = INT_MIN, cur = res, l = -1, r = -1, lasti = 0;
            for (int i = 0; i < n; i++) {
                if (A[i] == 0) {
                    haszero = true;
                    if (cur < 0) {
                        cur = shrink(A, n, cur, l, r, lasti, i);
                    }
                    res = max(res, cur);
                    cur = INT_MIN;
                    l = r = -1;
                    lasti = i+1;
                    continue;
                }

                if (A[i] < 0) {
                    if (l < 0) l = i;
                    r = i;
                }

                if (cur == INT_MIN) {
                    cur = A[i];
                } else 
                    cur *= A[i];
            }

            if (cur < 0) {
                cur = shrink(A, n, cur, l, r, lasti, n);
            }
            res = max(cur, res);

            return haszero ? max(res, 0) : res;
        }
};

void test(int A[], int n) {
	cout << Solution().maxProduct(A, n) << endl;
}

int main(int argc, char const *argv[])
{
    {
        int A[] = {1,0,-1,2,3,-5,-2};
        test(A, sizeof A/sizeof(A[0])); // 60
    }
    {
        int A[] = {1,0,-1,2,3,-5,-2, 0, -1, -2, -10, -4, 1, 1, 0, 0};
        test(A, sizeof A/sizeof(A[0])); // 80
    }
    {
        int A[] = {2, 3, -3, 4};
        test(A, sizeof A/sizeof(A[0])); // 6
    }
    {
        int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        test(A, sizeof A/sizeof(A[0])); // 960
    }
    {
        int A[] = {-2, -3, -1, -2, 1, -5};
        test(A, sizeof A/sizeof(A[0])); // 30
    }
    {
        int A[] = {-10};
        test(A, sizeof A/sizeof(A[0])); // -10
    }
    {
        int A[] = {3,-2,-3,-3,1,3,0};
        test(A, sizeof A/sizeof(A[0])); // 27
    }   
    {
        int A[] = {3,-2,-3,-3,1,3, 0, 4, 5, -1, -2, 2};
        test(A, sizeof A/sizeof(A[0])); // 80
    }   
    {
        int A[] = {0,-3,1,1};
        test(A, sizeof A/sizeof(A[0])); // 1
    }
    {
        int A[] = {-2, 0,-1};
        test(A, sizeof A/sizeof(A[0])); // 0
    }
	return 0;
}
