
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        std::vector<vector<int>> res;
        TreeNode* nd = root;
        if (!nd) return res;

        queue<TreeNode*> q;
        q.push(nd);
        res.push_back({nd->val});

        while (q.size()) {
        	std::vector<int> sp;
        	int len = q.size();
        	while (len) {
        		auto& x = q.front();
        		q.pop();
        		if (x->left) {
        			sp.push_back(x->left->val);
        			q.push(x->left);
        		}
        		if (x->right) {
        			sp.push_back(x->right->val);
        			q.push(x->right);
        		}
        		len--;        		
        	}
        	if (sp.size()) res.insert(res.begin(), sp);
        }

        return res;
    }
};

void test(TreeNode *p) {
	cout << Solution().levelOrderBottom(p) << endl;
}

int main(int argc, char const *argv[])
{
    test(NULL); // {}
    {
        TreeNode n1 {1};
        test(&n1); // {{1}}
    }
    {
        TreeNode n1 {1, new TreeNode {2}};
        test(&n1); // 0
    }

    {
        TreeNode n1 {
            1,
            new TreeNode {
                2, NULL,
                new TreeNode {4}
            },
            new TreeNode {2}
        };
        TreeNode n2 {
            1,
            new TreeNode {
                2, NULL,
                new TreeNode {4}
            },
            new TreeNode {
                2, NULL,
                new TreeNode {4}}
        };
        TreeNode n3 {
            1,
            new TreeNode {
                2, NULL,
                new TreeNode {4}
            },
            new TreeNode {
                2, 
                new TreeNode {4}}
        };
        test(&n1); // 0
        test(&n2); // 0
        test(&n3); // 1
    }
    return 0;    
}