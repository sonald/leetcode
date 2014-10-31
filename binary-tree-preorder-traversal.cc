#include <iostream>
#include <vector>
#include <cmath>
#include <list>
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

class Solution {
    public:
        vector<int> preorderTraversal(TreeNode* root) {
            vector<int> res;
            if (!root) return res;
            
            list<TreeNode*> ss;
            ss.push_back(root);
            while (ss.size()) {
                auto t = ss.front();
                res.push_back(t->val);
                ss.pop_front();

                if (t->right) ss.push_front(t->right);
                if (t->left) ss.push_front(t->left);
            }

            return res;
        }

        vector<int> preorderTraversal2(TreeNode* root) {
            vector<int> res;
            if (!root) return res;
            
            res.push_back(root->val);
            if (root->left) {
                auto lhs = preorderTraversal(root->left);
                ::copy(lhs.begin(), lhs.end(), ::back_inserter(res));

            }
            if (root->right) {
                auto rhs = preorderTraversal(root->right);
                ::copy(rhs.begin(), rhs.end(), ::back_inserter(res));
            }

            return res;
        }
};

ostream& operator<<(ostream& os, vector<int>& v)
{
    for(auto x: v) os << x;
    return os;
}

int main(int argc, char *argv[])
{
    TreeNode root {1, new TreeNode{4, new TreeNode{2}, nullptr}, new TreeNode{3}};
    Solution sol;
    auto v = sol.preorderTraversal(&root);
    cout << v << endl;
    
    return 0;
}
