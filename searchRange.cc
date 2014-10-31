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
	// this is not garanteed as O(lgN)
    vector<int> searchRange(int A[], int n, int target) {
        std::vector<int> res {-1, -1};
        if (n == 0) return res;

        int l = 0, r = n-1, m = (l+r)/2;
        while (l <= r) {
        	m = (l+r)/2;
        	if (A[m] == target) {
        		int k = m-1;
        		while (k >= 0 && A[k] == target) k--;
        		res[0] = k+1;
        		k = m+1;
        		while (k < n && A[k] == target) k++;
        		res[1] = k-1;
        		break;
        	} else if (A[m] > target) {
        		r = m-1;
        	} else {
        		l = m + 1;
        	}
        }
        return res;
    }
};

class Solution2 {
public:
	// this is not garanteed as O(lgN)
    vector<int> searchRange(int A[], int n, int target) {
        std::vector<int> res {-1, -1};
        if (n == 0) return res;

        int l = 0, r = n-1, m = (l+r)/2;
        while (l <= r) {
        	m = (l+r)/2;
        	if (A[m] >= target) {
        		if (m == 0 && A[m] == target) {
        			res[0] = m; break;
        		}
        		r = m-1;
        	} else {
        		l = m + 1;
        		if (l == n || A[l] == target) {
        			res[0] = l == n ? -1 : l;
        			break;
        		}        			
        	}
        }

        l = 0, r = n-1, m = (l+r)/2;
        while (l <= r) {
        	m = (l+r)/2;
        	if (A[m] <= target) {
        		if (m == n-1 && A[m] == target) {
        			res[1] = n-1; break;
        		}
        		l = m + 1;
        	} else {
        		r = m - 1;
        		if (r == -1 || A[r] == target) {
        			res[1] = r;
        			break;
        		}        			
        	}
        }

        return res;
    }
};

void test(int A[], int n, int target) 
{
	cout << Solution2().searchRange(A, n, target) << endl;	
}

int main(int argc, char const *argv[])
{
	{
		int A[] = {1};
		test(A, 1, 2);
	}
	{
		int A[] = {5, 7, 7, 8, 8, 10};
		test(A, 6, 8);
	}
	{
		int A[] = {8, 8, 8, 8, 8, 8, 8};
		test(A, 7, 8);
	}

	return 0;
}
