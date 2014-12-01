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

//O(1) space
class Solution2 {
public:
    void flatten(TreeNode *root) {
        TreeNode* n = root;
        while (n) {
            if (n->left) { 
                auto* l = n->left;
                while (l->right) l = l->right;
                l->right = n->right;
                n->right = n->left;
                n->left = nullptr; 
            }
            n = n->right;
        }
    }
};

class Solution {
public:
    void flatten(TreeNode *root) {
        sub(root);
    }

    TreeNode* sub(TreeNode* root) {
        if (!root) return NULL;
        auto* t = sub(root->left);
        auto* t2 = sub(root->right);
        root->left = nullptr;
        if (t) {
            root->right = t;
            while (t->right) t = t->right;
            t->right = t2;
        }
        return root;
    }
};

void dump(TreeNode* nd) { // preorder
    std::vector<TreeNode*> sp;
    sp.push_back(nd);
    while (sp.size()) {
        auto* p = sp.back(); sp.pop_back();
        if (p) cout << p->val << " ";
        else cout << "# ";
        if (p) {
            sp.push_back(p->right);
            sp.push_back(p->left);
        }
    }
    cout << endl;
}

void test(TreeNode* n) {
	Solution2().flatten(n);
    dump(n);
}

int main(int argc, char const *argv[])
{
    {
        TreeNode n{1,
            new TreeNode{2,
                new TreeNode{3},
                new TreeNode{4}},
            new TreeNode{5,
                nullptr, 
                new TreeNode{6}}};
        test(&n);
    }
    return 0;    
}
