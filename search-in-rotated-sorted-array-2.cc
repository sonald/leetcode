#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cassert>

using namespace std;
ostream& operator<<(ostream& os, const pair<int, int>& v)
{
    return os << "(" << v.first << "," << v.second << ")";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]";
}

template <class T, class U>
ostream& operator<<(ostream& os, const map<T, U>& v)
{
    os << "{";
    for (auto& x: v) {
        os << "{" << x.first << ", " << x.second << "} ";
    }
    return os << "}";
}

class Solution {
public:
    bool search(int A[], int n, int target) {
        int l = 0, r = n-1, m = 0;
        if (n == 0) return false;
        if (A[0] == target) return true;
        else if (A[n-1] == target) return true;

        if (A[l] == A[r]) {
            while (l < r && A[l] == A[l+1]) l++;
            l++;
            while (l < r && A[r] == A[r-1]) r--;
        }

        while (l <= r) {
            m = (l+r)/2;
            if (A[m] == target) return true;
            
            if (A[m] > target) {
                if (A[0] <= A[m] && A[0] > target) {
                        l = m + 1;
                } else
                    r = m - 1;

            } else {
                if (A[0] <= A[m])
                    l = m + 1;
                else {
                    if (A[0] > target)
                        l = m + 1;
                    else
                        r = m - 1;
                }
            }
        }

        return false;
    }
};

#define LEN(a) (sizeof(a)/sizeof(a[0]))

void test(int A[], int n, int target) 
{
    cout << Solution().search(A, n, target) << endl;    
}

int main(int argc, char const *argv[])
{
    {
        int A[] = {1};
        test(A, 1, 0); // 0
    }
    {
        int A[] = {1, 1, 1};
        test(A, 1, 0); // 0
    }
    {
        int A[] = {1, 3, 1, 1, 1};
        test(A, LEN(A), 3); // 1
    }
	{
        int A[] = {2, 2, 4, 5, 6, 7, 0, 1, 2, 2};
        test(A, LEN(A), 4);     // 1   
    }
    cout << endl;

    for (int i = 0; i <= 7; i++) {
        int A[] = {4, 5, 6, 7, 0, 1, 2};
        test(A, 7, i); 
    }
    cout << endl;

     for (int i = 0; i <= 8; i++) {
        int A[] = {4, 5, 6, 7, 8, 1, 2, 3};
        test(A, 8, i); 
    }
    cout << endl;

     for (int i = 0; i <= 5; i++) {
        int A[] = {5, 1, 2, 3, 4};
        test(A, 5, i); 
    }    
    cout << endl;

    {
        int A[] = {3,4,5,1,2};
        test(A, 5, 4);
    }

	return 0;
}
