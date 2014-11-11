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
    int maxDepth(TreeNode *root) {
        if (!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right))+1;
    }
};

void test(TreeNode *n) {
	cout << Solution().maxDepth(n) << endl;
}

int main(int argc, char const *argv[])
{
    {
        test(NULL);
    }
    {
        TreeNode n1 {1};
        test(&n1);
    }
    {
        TreeNode n1 {1, new TreeNode {2}};
        test(&n1);
    }

    {
        TreeNode n1 {
            1,
            new TreeNode {
                2, 
                NULL,
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
            new TreeNode {
                3,
                new TreeNode {
                    5,
                    new TreeNode {
                        6
                    }
                }
            }
        };
        test(&n1);
        cout << "---------\n";
        test(&n2);
    }
    return 0;    
}