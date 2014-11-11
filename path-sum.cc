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

// morris-preorder, intrusive
class Solution4 {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;

        bool ret = false;
        TreeNode* nd = root;
        while (nd) {
            if (!nd->left) {
                //NOTE: can not write `return true` here. since morris traversion modified
                //struture of tree, we need to run over to make sure all changes restored.
                //because of this, this may not as fast as primitive solution.
                if (!nd->right && nd->val == sum) ret = true;
                if (nd->right) nd->right->val += nd->val;                
                nd = nd->right;
            } else {
                auto* l = nd->left;
                while (l->right && l->right != nd) l = l->right;
                if (l->right == nd) {
                    if (!l->left && l->val == sum) ret = true;                                                                        
                    nd = nd->right;
                    l->right = nullptr;
                } else {
                    nd->left->val += nd->val;                    
                    if (nd->right) nd->right->val += nd->val;                    
                    l->right = nd;
                    nd = nd->left;
                }
            }
        }

        return ret;
    }
};

// non-recursive, intrusive
class Solution3 {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;

        std::vector<TreeNode*> sp;
        sp.push_back(root);
        while (sp.size()) {    
            auto* np = sp.back();
            sp.pop_back();

            if (!np->left && !np->right) {                
                if (np->val == sum) return true;
            }

            if (np->left) {
                np->left->val += np->val;                        
                sp.push_back(np->left);
            }
            if (np->right) {
                np->right->val += np->val;                                        
                sp.push_back(np->right);
            }
        }

        return false;
    }
};

// non-recursive
class Solution2 {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;

        std::vector<TreeNode*> sp;
        unordered_map<TreeNode*, bool> accessed;

        sp.push_back(root);
        int len = 0;

        while (sp.size()) {    
            auto* np = sp.back();
            if (np->left && !accessed[np->left]) {
                len += np->val;                        
                sp.push_back(np->left);
            } else if (np->right && !accessed[np->right]) {
                len += np->val;                                        
                sp.push_back(np->right);
            } else {
                if (!np->left && !np->right)
                    if (len + np->val == sum) return true;
                accessed[np] = true;
                sp.pop_back();
                if (sp.size()) len -= sp.back()->val;
            }
        }

        return false;
    }
};

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right) 
            return root->val == sum;

        return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
    }
};

void test(TreeNode *n, int sum) {
    auto r = Solution4().hasPathSum(n, sum);
	cout << "#: " << r << endl;
}

int main(int argc, char const *argv[])
{
    {
        test(NULL, 0); // 0
    }
    {
        TreeNode n1{1, new TreeNode{2}};
        TreeNode n2{1, NULL, new TreeNode{2}};        
        test(&n1, 3); // 1
        test(&n2, 3); // 1        
    }
    {
        TreeNode n1{1};
        test(&n1, 1); // 1
    }
    {
        TreeNode n1 {
            5,
            new TreeNode {
                4, 
                new TreeNode {
                    11,
                    new TreeNode {7 },
                    new TreeNode {2 },                    
                }
            },
            new TreeNode {
                8,
                new TreeNode{13},
                new TreeNode{
                    4, NULL,
                    new TreeNode {1}
                }
            }
        };

        TreeNode n2 {
            1,
            new TreeNode {
                2, NULL,
                new TreeNode {4}
            },
            new TreeNode {
                3,
                new TreeNode {
                    5,
                    new TreeNode {
                        6
                    }
                }
            }
        };
        // test(&n1, 23); // 0

        test(&n1, 22); // 1
        test(&n2, 7);  // 1
    }
    return 0;    
}