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
 * Definition for binary tree with next pointer.
*/
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x, TreeLinkNode* l = NULL, TreeLinkNode* r = NULL)
        : val(x), left(l), right(r), next(NULL) {}
};

class Solution {
    public:
        void connect(TreeLinkNode *root) {
            if (!root) return;
            if (root->left) {
                root->left->next = root->right;
                auto *l = root->left->right, *r = root->right->left;
                while (l) { l->next = r; l = l->right; r = r->left; }
                connect(root->left);
                connect(root->right);
            }
        }
};

void dump(TreeLinkNode* nd) { // preorder
    std::vector<TreeLinkNode*> sp;
    sp.push_back(nd);
    while (sp.size()) {
        auto* p = sp.back(); sp.pop_back();
        cout << (p && p->next? p->next->val:0) << " ";
        //if (p) cout << p->val << " ";
        //else cout << "# ";
        if (p) {
            sp.push_back(p->right);
            sp.push_back(p->left);
        }
    }
    cout << endl;
}

void test(TreeLinkNode *n) {
	Solution().connect(n);
    dump(n);
}

int main(int argc, char const *argv[])
{
    {
        TreeLinkNode n{1,
            new TreeLinkNode{2,
                new TreeLinkNode{4},
                new TreeLinkNode{5},
            },
            new TreeLinkNode{3,
                new TreeLinkNode{6},
                new TreeLinkNode{7},
            }
        };
        test(&n);
    }
    return 0;    
}
