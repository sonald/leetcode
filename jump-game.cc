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
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

class Solution {
public:
	//greedy way
    bool canJump(int A[], int n) {
    	if (n == 1) return true;
    	int sp = 0;
        for (int i = 0; i < n;) {
        	if (A[i] == 0) return false;

        	int t = A[i], id = i+1, m = t;
    		if (t + i >= n-1) return ++sp;

        	for (int j = 1; j <= t; ++j) {
        		if (m < j+A[i+j]) { 
        			m = j+A[i+j]; id = i+j;
        		}
        	}
        	sp++;
        	i = id;
        }

        return sp;
    }
}; 

void test(int A[], int n) {
	cout << Solution().canJump(A, n) << endl;
}

int main(int argc, char const *argv[])
{
	{
		int A[] = {3, 2, 1, 0, 4};
		test(A, sizeof A / sizeof(A[0]));  // false
	}

	{
		int A[] = {1, 2, 3, 4, 5, 6};
		test(A, sizeof A / sizeof(A[0]));  // 3
	}
	{
		int A[] = {2};
		test(A, sizeof A / sizeof(A[0]));  // true
	}
	{
		int A[] = {2, 1};
		test(A, sizeof A / sizeof(A[0]));  // 1
	}
	{
		int A[] = {2, 3, 1, 1, 0, 4};
		test(A, sizeof A / sizeof(A[0]));  // false
	}
	{
		int n = 25000;
		int A[n];
		for (int i = 0; i < n; ++i) {
			A[i] = n-i;
		}
		test(A, n);  // 1
	}
	{
		int A[] = {1, 2, 1, 1, 1};
		test(A, sizeof A / sizeof(A[0])); //3
	}
	{
		int n = 25000;
		int A[n];
		for (int i = 0; i < n; ++i) {
			A[i] = i+1;
		}
		test(A, n);  // 15
	}
	return 0;
}