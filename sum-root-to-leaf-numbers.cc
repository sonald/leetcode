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

class Solution2 {
    public:
        int sumNumbers(TreeNode *root) {
            if (!root) return 0;
            if (!root->left && !root->right) {
                return root->val;
            } else {
                int res = 0;
                if (root->left) { root->left->val += root->val*10; res += sumNumbers(root->left); }
                if (root->right) { root->right->val += root->val*10; res += sumNumbers(root->right); }
                return res; 
            }
        }
};

class Solution {
    public:
        int res = 0;
        int sumNumbers(TreeNode *root) {
            if (root) helper(root, 0);
            return res; 
        }

        void helper(TreeNode* nd, int sum) {
            if (!nd->left && !nd->right) { res += sum*10+nd->val; return; }
            if (nd->left) helper(nd->left, sum*10+nd->val);
            if (nd->right) helper(nd->right, sum*10+nd->val);
        }
};

void test(TreeNode *n) {
    auto r = Solution().sumNumbers(n);
	cout << "#: " << r << endl;
    cout << Solution2().sumNumbers(n) << endl;
}

int main(int argc, char const *argv[])
{
    {
        test(NULL); // 0
    }
    {
        TreeNode n1 { 2,
            new TreeNode { 4 }, 
            new TreeNode { 3,
                    new TreeNode {1} } };
        test(&n1);
    }
    {
        TreeNode n1 {1,
            new TreeNode {2, 
                new TreeNode { 3,
                    new TreeNode {1 }, },
                new TreeNode {2 } },
            new TreeNode { 3,
                new TreeNode{1},
                new TreeNode{ 4, 
                    new TreeNode{5},
                    new TreeNode {1} } } };
        test(&n1);
    }
    {
        TreeNode n1 { 1,
            new TreeNode { 4, 
                new TreeNode { 1 }},
            new TreeNode { 2,
                new TreeNode{1},
                new TreeNode{ 4, 
                    new TreeNode{5},
                    new TreeNode {1} } } };
        test(&n1);
    }
    return 0;    
}
