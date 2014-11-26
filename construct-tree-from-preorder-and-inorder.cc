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

class Solution2 {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        TreeNode dummy {0};                
        std::vector<TreeNode*> sp {&dummy};

        TreeNode** pp = &dummy.left;
        int i = 0, j = 0, n = preorder.size();
        while (i < n) {
            auto* t = new TreeNode {preorder[i]};        
            *pp = t;
            pp = &t->left;
            sp.push_back(t);
            i++;
            if (i == preorder.size()) break;            
            if (preorder[i-1] == inorder[j]) {
                 while (sp.size() > 2 && inorder[j+1] == sp[sp.size()-2]->val) {
                     sp.pop_back();
                    j++;
                }

                pp = &sp.back()->right;
                sp.pop_back(); 
                j++;
            }
        }
        return dummy.left;
    }
};

class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return helper(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }

    TreeNode *helper(vector<int> &pre, int l, int r, vector<int> &in, int s, int e) {
        if (l > r) return nullptr;
        auto* root = new TreeNode {pre[l]};
        int m = s;
        for  (m = s; m <= e; m++) {
            if (in[m] == pre[l]) break;
        }

        root->left = helper(pre, l+1, l+(m-s), in, s, m-1);
        root->right = helper(pre, l+(m-s)+1, r, in, m+1, e);
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

void test(vector<int> &preorder, vector<int> &inorder) {
    auto* nd = Solution().buildTree(preorder, inorder);
    dump(nd);
    auto* nd2 = Solution2().buildTree(preorder, inorder);    
    dump(nd2);
}

int main(int argc, char const *argv[])
{
    {
        std::vector<int> pre {1, 2};
        std::vector<int> in {2, 1};
        test(pre, in);
    }
    {
        std::vector<int> pre {4, 2, 1, 3, 6, 5};
        std::vector<int> in {1, 2, 3, 4, 5, 6};
        test(pre, in);
    }
    return 0;    
}
