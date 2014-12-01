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
        void connect(TreeLinkNode *nd) {
            if (!nd) return;
            TreeLinkNode* p = nullptr;

            while (nd) {
                TreeLinkNode* l = nd;
                while (p) {
                    if (p->left && p->left != l) {
                        l->next = p->left;
                        l = l->next;
                    }

                    if (p->right && p->right != l) {
                        l->next = p->right;
                        l = l->next;
                    }

                    p = p->next;
                }

                while (nd && !nd->left && !nd->right) {
                    nd = nd->next;
                }
                if (!nd) break;
                p = nd;
                if (nd->left) nd = nd->left;
                else if (nd->right) nd = nd->right;
            }
        }
};

void dump(TreeLinkNode* nd) { // preorder
    std::vector<TreeLinkNode*> sp;
    sp.push_back(nd);
    while (sp.size()) {
        auto* p = sp.back(); sp.pop_back();
        if (p && p->next) {
            cout << p->val << " ";
            cout << "(" << (p && p->next? p->next->val:0) << ") ";
        }
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
                new TreeLinkNode{4,
                    new TreeLinkNode{7},
                },
                new TreeLinkNode{5},
            },
            new TreeLinkNode{3,
                nullptr,
                new TreeLinkNode{6,
                    nullptr,
                    new TreeLinkNode{8},
                }
            }
        };
        test(&n);
    }
    {
        TreeLinkNode n{1,
            new TreeLinkNode{2,
                new TreeLinkNode{4,
                    new TreeLinkNode{5},
                    new TreeLinkNode{8},
                }
            },
            new TreeLinkNode{3,
                new TreeLinkNode{6,
                    nullptr,
                    new TreeLinkNode{7},
                }
            }
        };
        test(&n);
    }
    {
        TreeLinkNode n{-8,
            new TreeLinkNode{-6,
                new TreeLinkNode{6,
                    nullptr,
                    new TreeLinkNode{5},
                }
            },
            new TreeLinkNode{7}};
        test(&n);
    }
    //{-8,-6,7,6,#,#,#,#,5}


    {
        //{0,2,4,1,#,3,-1,5,1,#,6,#,8}
        TreeLinkNode n{0,
            new TreeLinkNode{2,
                new TreeLinkNode{1,
                    new TreeLinkNode{5},
                    new TreeLinkNode{1},
                }
            },
            new TreeLinkNode{4,
                new TreeLinkNode{3,
                    nullptr,
                    new TreeLinkNode{6},
                },
                new TreeLinkNode{-1,
                    nullptr,
                    new TreeLinkNode{8},
                }
            }
        };
        test(&n);
    }


    return 0;    
}
