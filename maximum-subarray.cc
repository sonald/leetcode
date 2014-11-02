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

class Solution {
public:
    int maxSubArray(int A[], int n) {
        if (n <= 0) return 0;

        int m = A[0], edge = m;
        for (int i = 1; i < n; i++) {
            edge = max(edge+A[i], A[i]);
            if (m <= edge) {
                m = edge;
            }
        }

        return m;
    }
};

void test(int A[], int n) {
	cout << Solution2().maxSubArray(A, n) << endl;
}

int main(int argc, char const *argv[])
{
    {
        int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        test(A, sizeof A/sizeof(A[0]));
    }
    {
        int A[] = {-2, -3, -1, -2, -1, -5};
        test(A, sizeof A/sizeof(A[0]));
    }
    {
        int A[] = {-10};
        test(A, sizeof A/sizeof(A[0]));
    }
    {
        int A[] = {3,-2,-3,-3,1,3,0};
        test(A, sizeof A/sizeof(A[0])); // 4        
    }   
	return 0;
}
