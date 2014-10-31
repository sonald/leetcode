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


class Solution2 {
public:
    int findPivot(int A[], int n) {
        int l = 0, r = n-1, m;
        if (A[l] < A[r]) return 0;

        while (l <= r) {
            m = (l+r)/2;
            if (A[m] > A[m+1]) break;
            if (A[0] > A[m]) {
                r = m - 1;
            } else {
                l = m + 1;
            }            
        }
        return m+1;
    }

    int search(int A[], int n, int target) {
        int l = 0, r = n-1, m = 0;
        if (n == 0) return -1;
        if (A[0] == target) return 0;        
        else if (A[n-1] == target) return n-1;

        int pivot = findPivot(A, n);
        if (!pivot || A[0] > target) {
            l = pivot;
        } else {
            r = pivot-1;
        }
        while (l <= r) {
            m = (l+r)/2;
            if (A[m] == target) return m;
            if (A[m] > target) r = m - 1;
            else l = m + 1;
        }

        return -1;
    }
  
};

class Solution {
public:
    int search(int A[], int n, int target) {
        int l = 0, r = n-1, m = 0;
        if (n == 0) return -1;
        if (A[0] == target) return 0;        
        else if (A[n-1] == target) return n-1;

        while (l <= r) {
            m = (l+r)/2;
            // cout << "l " << l << ", r " << r << ", m " << m << endl;
            if (A[m] == target) return m;
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

        return -1;
    }
};

void test(int A[], int n, int target) 
{
    cout << (Solution2().search(A, n, target) == Solution().search(A, n, target)) << " ";
    cout << Solution2().search(A, n, target) << endl;    
}

int main(int argc, char const *argv[])
{
	
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
