#include <iostream>
#include <vector>
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

class Solution {
public:
    void sortColors(int A[], int n) {
        if (n == 0) return;
        int l = 0, r = n - 1;
        int p = 0;
        while (p <= r) {
            if (A[p] == 0) {
                auto t = A[l]; A[l] = A[p]; A[p] = t;
                while (A[l] == 0) l++;
                if (p < l) p = l;

            } else if (A[p] == 2) {
                auto t = A[r]; A[r] = A[p]; A[p] = t;
                while (A[r] == 2) r--;

            } else p++;
        }
    }
};

void test(int A[], int n) {
    for_each(A, A+n, [](int i) { cout << i << " "; });
    cout << endl;

    Solution().sortColors(A, n);
    for_each(A, A+n, [](int i) { cout << i << " "; });
    cout << endl;
}

int main(int argc, char const *argv[])
{
    {
        int A[] = {1, 0};
        test(A, sizeof A / sizeof A[0]);
    }
    {
        int A[] = {1, 0, 2};
        test(A, sizeof A / sizeof A[0]);
    }

    {
        int A[] = {2, 1, 0};
        test(A, sizeof A / sizeof A[0]);
    }
    {
        int A[] = {2, 0, 1, 0, 2, 1, 2, 1, 0, 1, 2, 0};
        test(A, sizeof A / sizeof A[0]);
    }
    return 0;
}