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
    TreeNode(int x, TreeNode* l = NULL, TreeNode* r = NULL) : val(x), left(l), right(r) {}
};

class Solution {
public:
    bool isValidBST(TreeNode *root) {
        if (!root) return true;
        return helper(root, INT_MIN, INT_MAX);
    }

    bool helper(TreeNode* nd, int bl, int br) {
        if (!nd) return true;
        auto val = nd->val;

        if (nd->left) {
            if (nd->left->val < bl || nd->left->val >= val 
                || !helper(nd->left, bl, val-1)) 
                return false;
        }
        if (nd->right) {
            if (nd->right->val > br || nd->right->val <= val 
                || !helper(nd->right, val+1, br))
             return false;
        }

        return true;
    }
};

void test(TreeNode *p) {
	cout << Solution().isValidBST(p) << endl;
}

int main(int argc, char const *argv[])
{
    test(NULL);
    {
        TreeNode n1 {1};
        test(&n1);
    }
    {
        TreeNode n1 {2, new TreeNode {1}};
        test(&n1);
    }

    {
        TreeNode n1 {3, 
            new TreeNode {1, NULL, new TreeNode {2} }, 
            new TreeNode {5} };
        TreeNode n2 {
            3,
            new TreeNode {2, NULL, new TreeNode {4} },
            new TreeNode {3} };
        test(&n1); // 1
        test(&n2); // 0
    }
    {
        //10,5,15,#,#,6,20
        TreeNode n1 {10, 
            new TreeNode {5},
            new TreeNode {15,
                new TreeNode{6},
                new TreeNode{20}}};
        test(&n1); // 0
    }
    return 0;    
}