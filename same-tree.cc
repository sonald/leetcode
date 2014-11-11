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

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (!p || !q) {
            return (!p && !q);
        }

        if (p->val != q->val) return false;
        if (p->left && q->left) {
            if (!isSameTree(p->left, q->left)) return false;
        } else if (p->left || q->left) {
            return false;
        }

        if (p->right && q->right) {
            if (!isSameTree(p->right, q->right)) return false;
        } else if (p->right || q->right) {
            return false;
        }

        return true;
    }
};

void test(TreeNode *p, TreeNode *q) {
	cout << Solution().isSameTree(p, q) << endl;
}

int main(int argc, char const *argv[])
{
    {
        test(NULL, NULL);
    }
    {
        TreeNode n1 {1};
        TreeNode n2 {2};
        test(&n1, &n2);
    }
    {
        TreeNode n1 {1, new TreeNode {2}};
        TreeNode n2 {1, new TreeNode {2}};
        test(&n1, &n2);
    }

    {
        TreeNode n1 {
            1,
            new TreeNode {
                2, NULL,
                new TreeNode {4}
            },
            new TreeNode {3}
        };
        TreeNode n2 {
            1,
            new TreeNode {
                2, NULL,
                new TreeNode {4}
            },
            new TreeNode {3}
        };
        test(&n1, &n2);
    }
    return 0;    
}