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
    bool balanced = true;
    int depth(TreeNode* nd) {        
        if (!nd) return 0;

        int l = depth(nd->left), r = depth(nd->right);
        if (abs(l-r) > 1) balanced = false;
        return max(l, r) + 1;
    }

    bool isBalanced(TreeNode *root) {
        if (!root) return true;
        depth(root);
        return balanced;
    }
};

void test(TreeNode *n) {
    auto r = Solution().isBalanced(n);
	cout << "#: " << r << endl;
}

int main(int argc, char const *argv[])
{
    {
        test(NULL); // 0
    }
    {
        TreeNode n1 {
            5,
            new TreeNode {
                4, 
                new TreeNode {
                    11,
                    new TreeNode {7 },
                },
                new TreeNode {2 }                    
            },
            new TreeNode {
                8,
                new TreeNode{13},
                new TreeNode{
                    4, 
                    new TreeNode{5},
                    new TreeNode {1}
                }
            }
        };
        test(&n1);
    }
    {
        TreeNode n1 {
            5,
            new TreeNode {
                4, 
                new TreeNode {
                    11,
                    new TreeNode {7 },
                    new TreeNode {2 },                    
                }
            },
            new TreeNode {
                8,
                new TreeNode{13},
                new TreeNode{
                    4, 
                    new TreeNode{5},
                    new TreeNode {1}
                }
            }
        };

        test(&n1);
    }
    return 0;    
}