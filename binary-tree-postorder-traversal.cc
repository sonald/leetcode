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
    TreeNode(int x): val{x}, left{nullptr}, right{nullptr} {}
    TreeNode(int x, TreeNode *l ,TreeNode *r): val{x}, left{l}, right{r} {}
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

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;

        TreeNode dummy {INT_MIN};
        dummy.left = root;
        TreeNode* nd = &dummy;

        vector<TreeNode*> sp {&dummy};
        while (sp.size() > 0) {
            if (nd && sp.back()->left) {
                sp.push_back(sp.back()->left);
                nd = sp.back();
            } else {
                if (!sp.back()->right || (res.size() && sp.back()->right->val == res.back())) {
                    res.push_back(sp.back()->val);
                    sp.pop_back();
                    nd = NULL;
                } else {
                    sp.push_back(sp.back()->right);
                    nd = sp.back();
                }
            }
        }

        res.pop_back();
        return res;
    }
};

void test(TreeNode* nd) {
    cout << Solution().postorderTraversal(nd) << endl;
}

int main(int argc, char *argv[])
{
    test(NULL);
    {
        TreeNode root {
            1, 
            new TreeNode{
                4, 
                new TreeNode{2}, new TreeNode{7}},
            new TreeNode{3}
        };
        test(&root);
    }

    {
        TreeNode root {
            1, 
            new TreeNode{4, new TreeNode{2, nullptr, new TreeNode{6}}, nullptr},
            new TreeNode{3, NULL, new TreeNode{5}}
        };
        test(&root);
    }

    return 0;
}
