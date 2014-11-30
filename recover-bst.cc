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

// O(1) space and O(n) time
class Solution2 {
public:
    TreeNode* n1 = nullptr, *n2 = nullptr;
    void recoverTree(TreeNode *root) {
        if (!root) return;

        TreeNode* prev = nullptr, *cur = nullptr;
        while (root) {
            if (!root->left) {
                prev = cur; cur = root;
                root = root->right;
            } else {
                auto* l = root->left;
                while (l->right && l->right != root) l = l->right;
                if (l->right == root) {
                    prev = cur; cur = root;
                    root = root->right;
                    l->right = nullptr;
                } else {
                    l->right = root;
                    root = root->left;
                }
            }
            if (prev && prev->val > cur->val) {
                if (!n1) { n1 = prev; n2 = cur; } 
                else { n2 = cur; }
            }
        }

        std::swap(n1->val, n2->val);
    }
};

// O(n) space and time
class Solution {
public:
    TreeNode* n1 = nullptr, *n2 = nullptr;
    void recoverTree(TreeNode *root) {
        if (!root) return;
        //inorder traversal
        vector<TreeNode*> sp;
        TreeNode* nd = root, *prev = nullptr;
        while (sp.size() || nd) {
            while (nd) { sp.push_back(nd); nd = nd->left; }
            nd = sp.back(); sp.pop_back();
            //if (n1 && n1->val < nd->val) break;

            if (prev && prev->val > nd->val) {
               if (!n1) { n1 = prev; n2 = nd; } 
               else { n2 = nd; break; }
            }
            prev = nd;
            nd = nd->right;
        }

        std::swap(n1->val, n2->val);
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

void test(TreeNode *p) {
    Solution2().recoverTree(p);    
    //Solution().recoverTree(p);    
    dump(p);
}

int main(int argc, char const *argv[])
{
    test(NULL);
    {
        TreeNode n1 {1, new TreeNode {2}};
        test(&n1);
    }
    {
        TreeNode n1 {2, 
            new TreeNode {1, NULL, new TreeNode {3} }, 
            new TreeNode {5} };
        TreeNode n2 {2,
            new TreeNode {4, new TreeNode {1}, new TreeNode {3} },
            new TreeNode {5} };
        test(&n1); // 1
        test(&n2); // 0
    }
    {
        TreeNode n1 {5,
            new TreeNode {7,
                new TreeNode {1},
                new TreeNode {4, 
                    new TreeNode {3}}
            },
            new TreeNode {8,
                new TreeNode{2,
                    new TreeNode {6}},
                new TreeNode{9}}};
        test(&n1); // 0
    }
    return 0;    
}
