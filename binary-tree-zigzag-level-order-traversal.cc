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


template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    cout << "[";
    for(auto x: v) os << x << " ";
    return os << "]";
}

class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if (!root) return res;
        //why the heck Runtime Error if replace list with vector
        list<TreeNode*> sp { root };

        int level = 0;
        while (sp.size()) {
            auto oldlen = sp.size();
            int i = 0;
            std::vector<int> l;
            while (i < oldlen) {
                auto& x = sp.front();
                if (level % 2 == 0) l.push_back(x->val);
                else l.insert(l.begin(), x->val);
                if (x->left) sp.push_back(x->left);
                if (x->right) sp.push_back(x->right);
                sp.pop_front();
                i++;
            }
            res.push_back(l);
            level++;
        }

        return res;
    }
};


void test(TreeNode* nd) {
    cout << Solution().zigzagLevelOrder(nd) << endl;
}

int main(int argc, char *argv[])
{
    test(NULL);
    {
        TreeNode nd { 1};
        test(&nd);
    }
    {
        TreeNode nd { 1, new TreeNode {2}, nullptr};
        test(&nd);
    }
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
            new TreeNode{4, new TreeNode{2, new TreeNode {7}, new TreeNode{6}}, nullptr},
            new TreeNode{3, NULL, new TreeNode{5}}
        };
        test(&root);
    }

    return 0;
}
