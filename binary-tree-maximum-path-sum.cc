#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <unordered_map>
#include <random>
#include <map>
#include <algorithm>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left{nullptr}, *right{nullptr};
    TreeNode(int x, TreeNode *l=nullptr,TreeNode *r=nullptr): val{x}, left{l}, right{r} {}
};


ostream& operator<<(ostream& os, const vector<int>& v)
{
    for(auto x: v) os << x << " ";
    return os;
}

ostream& operator<<(ostream& os, const vector<TreeNode*>& v)
{
    for(auto x: v) os << x->val << " ";
    return os;
}

//better
class Solution2 {
    public:
        int res = INT_MIN;
        int maxPathSum(TreeNode *root) {
            helper(root);
            return res;
        }

        int helper(TreeNode *root) {
            if (!root) return 0;

            auto l = helper(root->left);
            auto r = helper(root->right);

            if (l < 0 || r < 0) {
                auto x = max(root->val, root->val + std::max(r, l));
                res = std::max(res, x);
                return x;
            } else {
                res = std::max(l + root->val + r, res);
                return std::max(l+root->val, r+root->val);
            }
        }
};


// explicitly show all states
class Solution {
    public:
        struct data {
            int max, side, curve;
            data(): max(0), side(0), curve(0) {}
        };

        int maxPathSum(TreeNode *root) {
            if (!root) return 0; // impossible
            return helper(root).max;
        }

        int max(int a, int b, int c) {
            return std::max(a, std::max(b, c));
        }

        data helper(TreeNode* nd) {
            data d;
            if (!nd->left && !nd->right) {
                d.max = d.side = d.curve = nd->val;
            } else {
                data ld, rd;
                if (nd->left) ld = helper(nd->left);
                if (nd->right) rd = helper(nd->right);

                if (nd->left && nd->right) {
                    if (ld.side >= 0 && rd.side >= 0) 
                        d.curve = std::max(nd->val, nd->val + rd.side + ld.side);
                    else
                        d.curve = max(nd->val, nd->val + rd.side, nd->val + ld.side);
                    d.curve = max(d.curve, ld.curve, rd.curve);
                }
                
                if (nd->left) {
                    ld.side = std::max(nd->val, ld.side + nd->val);
                    ld.max = std::max(ld.side, ld.max);
                    if (!nd->right) {
                        d.curve = std::max(ld.max, ld.side);
                        rd = ld;
                    }
                }

                if (nd->right) {
                    rd.side = std::max(nd->val, rd.side + nd->val);
                    rd.max = std::max(rd.side, rd.max);
                    if (!nd->left) {
                        d.curve = std::max(rd.max, rd.side);
                        ld = rd;
                    } 
                } 

                d.max = max(ld.max, rd.max, d.curve);
                d.side = std::max(ld.side, rd.side);
            }

            return d;
        }
};

void test(TreeNode* nd) {
    cout << Solution().maxPathSum(nd) << endl;
    cout << Solution2().maxPathSum(nd) << endl;
}

int main(int argc, char *argv[])
{
    //test(NULL);
    {
        TreeNode root { 1, 
            new TreeNode{ 4, 
                new TreeNode{2}, new TreeNode{7}},
            new TreeNode{3}
        };
        test(&root); //15
    }

    {
        TreeNode root { 1, 
            new TreeNode{4, new TreeNode{2, nullptr, new TreeNode{6}}, nullptr},
            new TreeNode{3, NULL, new TreeNode{5}}
        };
        test(&root); // 21
    }
    {
        TreeNode n {-2, 
            new TreeNode{-1}};
        test(&n);
    }

    //{1,-2,-3,1,3,-2,#,-1}
    {
        TreeNode n {1,
            new TreeNode{-2,
                new TreeNode{1,
                    new TreeNode{-1}},
                new TreeNode{3}},
            new TreeNode{-3,
                new TreeNode {-2}}};
        test(&n); // 3
    }
    return 0;
}
