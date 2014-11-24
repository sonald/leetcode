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

class Solution {
public:
    using Level = std::vector<TreeNode*>;
    vector<TreeNode *> generateTrees(int n) {
        if (n == 0) return {nullptr};

        std::vector<Level> f(n+1);
        f[1] = { new TreeNode{1} };
        for (int i = 2; i <= n; i++) {
            auto& l = f[i];
            for (int j = 0; j < i; j++) {
                auto&& v = merge(f, j ,i-j-1);
                for (auto&& x: v) {
                    l.push_back(x);
                }
            }
        }
        return f[n];
    }

    Level merge(std::vector<Level> f, int i, int j) {
        Level res;
        auto& l = f[i];
        auto& r = f[j];
        int n = max((int)l.size(), 1), m = max((int)r.size(), 1);
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                TreeNode* nd = new TreeNode(0);
                if (l.size()) cloneTree(&nd->left, l[i]);
                if (r.size()) cloneTree(&nd->right, r[j]);
                res.push_back(decorateTree(nd));
            }
        }

        return res;
    }

    void cloneTree(TreeNode** pp, TreeNode* nd) {
        if (!nd) return;
        TreeNode* n = new TreeNode {nd->val};
        *pp = n;
        if (nd->left) cloneTree(&(*pp)->left, nd->left);
        if (nd->right) cloneTree(&(*pp)->right, nd->right);
    }

    TreeNode* decorateTree(TreeNode* nd) {
        //inorder
        auto* root = nd;
        int i = 1;
        std::vector<TreeNode*> sp;
        while (nd || sp.size()) {
            while (nd) { sp.push_back(nd); nd = nd->left; }
            nd = sp.back(); sp.pop_back();
            nd->val = i++;
            nd = nd->right;
        }

        return root;
    }
};

class Solution2 {
public:
    vector<TreeNode *> generateTrees(int n) {
        if (n == 0) return {nullptr};        

        return helper(1, n);
    }

    vector<TreeNode*> helper(int l, int r) {
        if (l > r) return {nullptr};

        std::vector<TreeNode*> v;
        for (int id = l; id <= r; id++) {
            auto ls = helper(l, id-1);
            auto rs = helper(id+1, r);
            for (int i = 0; i < ls.size(); i++) {
                for (int j = 0; j < rs.size(); j++) {
                    auto *r = new TreeNode(id);
                    r->left = ls[i];
                    r->right = rs[j];
                    v.push_back(r);                    
                }
            }
        }
        return v;
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

void test(int n) {
    auto res = Solution2().generateTrees(n);    
	cout << res.size() << endl;
    for (auto& p: res) dump(p); 
}

int main(int argc, char const *argv[])
{
    // test(0);
    // test(1);
    test(2);
    test(3);
    // test(4);
    // 2
// Output: [{0,#,1},{0,1}]
// Expected:   [{1,#,2},{2,1}]

    return 0;    
}