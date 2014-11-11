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

// morris-preorder, intrusive
class Solution2 {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        if (!root) return {};

        std::vector<vector<int>> res;
        std::vector<int> sp;
        int cur = 0;

        TreeNode* nd = root;
        while (nd) {
            if (!nd->left) {
                cout << "pop " << nd->val << endl;
                sp.push_back(nd->val);
                cur += nd->val;
                if (!nd->right && cur == sum) {
                    res.push_back(sp);
                    cur -= nd->val;
                    sp.pop_back();
                } 
                nd = nd->right;
            } else {
                auto* l = nd->left;
                while (l->right && l->right != nd) l = l->right;
                if (l->right == nd) {
                    cout << "pop " << nd->val << endl;
                    sp.push_back(nd->val);                    
                    nd = nd->right;
                    l->right = nullptr;
                } else {
                    // nd->left->val += nd->val;                    
                    // if (nd->right) nd->right->val += nd->val;                    
                    sp.push_back(nd->val);
                    l->right = nd;
                    nd = nd->left;
                }
            }
        }

        return res;
    }
};

class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        if (!root) return {};
        if (!root->left && !root->right) {
            if (root->val == sum) {
                return {{root->val}};
            }
            return {};
        }

        std::vector<vector<int>> res;
        if (root->left) {
            auto p = pathSum(root->left, sum-root->val);
            for (auto& x: p) {
                x.insert(x.begin(), root->val);
                res.push_back(std::move(x));
            }
        }
        if (root->right) {
            auto p = pathSum(root->right, sum-root->val);
            for (auto& x: p) {
                x.insert(x.begin(), root->val);
                res.push_back(std::move(x));
            }
        }

        return res;
    }
};

void test(TreeNode *n, int sum) {
    auto r = Solution2().pathSum(n, sum);
	cout << "#: " << r << endl;
}

int main(int argc, char const *argv[])
{
    {
        test(NULL, 0); // 0
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
                    4, 
                    new TreeNode{5},
                    new TreeNode {1}
                }
            }
        };

        test(&n1, 22); // {{5,4,11,2},{5,8,4,5}}
    }
    return 0;    
}