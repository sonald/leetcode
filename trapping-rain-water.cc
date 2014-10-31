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
    int trap(int A[], int n) {
        int max_id = 0, highest = A[0];
        for (int i = 0; i < n; i++) {
            if (A[i] > highest) {
                highest = A[i]; max_id = i;
            }
        }

        int last = 0, res = 0;
        for (int i = 0; i <= max_id; i++) {
            if (A[i] >= last) {
                last = A[i];
            }
            res += (last - A[i]);
        }

        last = 0;
        for (int i = n-1; i >= max_id; i--) {
            if (A[i] >= last) {
                last = A[i];
            }
            res += (last - A[i]);
        }

        return res;
    }
};

class Solution2 {
public:
    int trap(int A[], int n) {
        int max_id = 0, highest = A[0];
        for (int i = 0; i < n; i++) {
            if (A[i] > highest) {
                highest = A[i]; max_id = i;
            }
        }

        int last = 0, res = 0;
        for (int i = 1; i <= max_id; i++) {
            if (A[i] >= A[last]) {
                res += calculate(A, last, i);
                last = i;
            }
        }

        last = n-1;
        for (int i = n-2; i >= max_id; i--) {
            if (A[i] >= A[last]) {
                res += calculate(A, i, last);
                last = i;
            }
        }

        return res;
    }

    int calculate(int A[], int from, int to) {
        int res = std::min(A[from], A[to]) * (to - from - 1);
        for (int i = from + 1; i < to; i++) 
            res -= A[i];
        return res;
    }
};

void test(int A[], int n) {
    cout << Solution().trap(A, n) << endl;
}

int main(int argc, char const *argv[])
{
    {
        int A[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        test(A, sizeof(A)/sizeof(A[0]));  // 6
    }
    {
        int A[] = {2, 0, 2};
        test(A, sizeof(A)/sizeof(A[0])); // 2
    }
    {
        int A[] = {0, 2};
        test(A, sizeof(A)/sizeof(A[0])); // 0
    }
    {
        int A[] = {2, 2, 2};
        test(A, sizeof(A)/sizeof(A[0])); // 0
    }
    {
        std::random_device rd;
     
        // Choose a random mean between 1 and 6
        std::default_random_engine e1(rd());
        std::uniform_int_distribution<int> uniform_dist(1, 100);

        int A[1000000];
        for (int i = 0; i < 1000000; i++) 
            A[i] = uniform_dist(e1);
        test(A, 1000000);
    }
	return 0;
}