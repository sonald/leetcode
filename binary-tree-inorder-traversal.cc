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

class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        vector<TreeNode*> sp;
        TreeNode* n = root;
        while (sp.size() || n) {
            while (n) { sp.push_back(n); n = n->left; }            
            n = sp.back();
            sp.pop_back();
            res.push_back(n->val);
            n = n->right;
        }

        return res;
    }
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        unordered_map<TreeNode*, bool> used;
        vector<int> res;
        if (!root) return res;

        list<TreeNode*> ss;
        ss.push_back(root);
        while (ss.size()) {
            auto t = ss.back();
            if (used[t] || t->left == nullptr) {
                ss.pop_back();
                res.push_back(t->val);
                if (t->right) ss.push_back(t->right);

            } else {
                if (t->left)
                    ss.push_back(t->left);
                used[t] = true;
            }
        }

        return res;
    }
};

void test(TreeNode* nd) {
    cout << Solution2().inorderTraversal(nd) << endl;        
    cout << Solution().inorderTraversal(nd) << endl;

}

int main(int argc, char *argv[])
{
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
            new TreeNode{4, new TreeNode{2}, nullptr},
            new TreeNode{3}
        };
        test(&root);
    }

    return 0;
}
