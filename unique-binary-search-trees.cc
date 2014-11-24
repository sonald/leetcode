#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

template<class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	bool f = true;
	os << "{";
    for (auto& t: v) {
    	if (f) os << "(" << t.first << "," << t.second << ")";
    	else os << "," << "(" << t.first << "," << t.second << ")";
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]";
}

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, TreeNode* l = NULL, TreeNode* r = NULL) 
        : val(x), left(l), right(r) {}
};

class Solution {
public:
    int numTrees(int n) {
        std::vector<int> f(n+1, 0);
        // if you need 4ms for Accepted, then use below
        // int f[n+1];
        // memset(f, 0, sizeof f);
        f[0] = 1, f[1] = 1;
        for (int i = 2; i <= n; i++) {            
            for (int j = 0; j < i; j++)  {
                f[i] += f[j] * f[i-j-1];
            }
        }

        return f[n];
    }
};

void test(int n) {
	cout << Solution().numTrees(n) << endl;
}

int main(int argc, char const *argv[])
{
    for (int i = 1; i < 10; i++) test(i);
    return 0;    
}