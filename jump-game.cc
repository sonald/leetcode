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
	//DP way
    int jump(int A[], int n) {
		std::vector<int> dp(n, 0);
        for (int i = n-2; i >= 0; i--) {
 			int t = A[i] + i >= n ? n - i - 1: A[i];
			dp[i] = 1 + dp[i+t];
			for (int j = t; j >= 1 && i+j < n; j--) {
				if (dp[i] == 1) break;
 				if (dp[i] > 1+dp[i+j]) dp[i] = 1 + dp[i+j];
			}
        }
        return dp[0];
    }
}; 

class Solution2 {
public:
	//greedy way
    int jump(int A[], int n) {
    	if (n == 1) return 0;
    	int sp = 0;
        for (int i = 0; i < n;) {
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
	cout << Solution2().jump(A, n) << endl;
}

int main(int argc, char const *argv[])
{
	{
		int A[] = {1, 2, 3, 4, 5, 6};
		test(A, sizeof A / sizeof(A[0]));  // 3
	}
	{
		int A[] = {2};
		test(A, sizeof A / sizeof(A[0]));  // 0
	}
	{
		int A[] = {2, 1};
		test(A, sizeof A / sizeof(A[0]));  // 1
	}
	{
		int A[] = {2, 3, 1, 1, 4};
		test(A, sizeof A / sizeof(A[0]));  // 2
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