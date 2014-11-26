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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {        
        TreeNode dummy {INT_MIN};                
        std::vector<TreeNode*> sp {&dummy};

        TreeNode** pp = &dummy.right;
        int n = inorder.size(), i = n-1, j = n-1;
        while (j >= 0) {
            if (sp.back()->val == inorder[i]) {
                pp = &sp.back()->left;
                sp.pop_back();
                i--;

            } else if (inorder[i] != postorder[j]) {
                auto* t = new TreeNode {postorder[j]};
                *pp = t;
                sp.push_back(t);
                pp = &t->right;
                j--;

            } else {
                auto* t = new TreeNode {postorder[j]};
                *pp = t;
                //sp.push_back(t);
                //sp.pop_back();  // push & pop
                pp = &t->left;
                j--;
                i--;
            }
        }

        return dummy.right;
    }
};

class Solution {
public:
    unordered_map<int, int> loc;
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {        
        for (int i = 0; i < inorder.size(); i++) {
            loc[inorder[i]] = i;
        }
        return helper(postorder, 0, postorder.size()-1, inorder, 0, inorder.size()-1);
    }

    TreeNode *helper(vector<int> &post, int l, int r, vector<int> &in, int s, int e) {
        if (l > r) return nullptr;
        auto* root = new TreeNode {post[r]};
        int m = loc[post[r]];
        root->left = helper(post, l, l+(m-s)-1, in, s, m-1);
        root->right = helper(post, l+(m-s), r-1, in, m+1, e);
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

void test(vector<int> &inorder, vector<int> &postorder) {
    auto* nd = Solution().buildTree(inorder, postorder);
    dump(nd);
    auto* nd2 = Solution2().buildTree(inorder, postorder);    
    dump(nd2);
}

int main(int argc, char const *argv[])
{
    {
        std::vector<int> post {2, 1};
        std::vector<int> in {2, 1};
        test(in, post);
    }
    {
        std::vector<int> post {1, 3, 2, 5, 6, 4};
        std::vector<int> in {1, 2, 3, 4, 5, 6};
        test(in, post);
    }
    {
        std::vector<int> in {2, 3, 9, 6, 1, 4, 8, 7, 5};
        std::vector<int> post {2, 9, 6, 3, 1, 7, 8, 5, 4};
        test(in, post);
    }
    return 0;    
}
