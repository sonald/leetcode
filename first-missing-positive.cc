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
    int firstMissingPositive(int A[], int n) {
        for (int i = 0; i < n; i++) {
            if (A[i] <= 0 || A[i] > n) {
                continue;
            } 

            int k = A[i];
            int p = A[k-1];
            while (k != p) {
                A[k-1] = k;
                k = p;
                if (p > n || p <= 0) break;
                p = A[k-1];
            }
        }

        for (int i = 0; i < n; i++) {
            if (A[i] != i+1) return i+1;
        }
        return n+1;
    }
};

void test(int A[], int n) {
	cout << Solution().firstMissingPositive(A, n) << endl;
}

int main(int argc, char const *argv[])
{
    {
        int A[] = {1,2,0};
        test(A, 3); // 3
    }
    {
        int A[] = {3,4,-1,1};
        test(A, 4); // 2
    }
    {
        int A[] = {2, 3, 7, -1, 4};
        test(A, 5); // 1
    }
    {
        int A[] = {2, 1};
        test(A, 2); // 3
    }
    {
        int A[] = {1, 1};
        test(A, 2); // 2
    }
	return 0;
}