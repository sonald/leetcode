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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
    public:
        BSTIterator(TreeNode *root) {
            auto *p = root;
            while (p) {
                _next.push_back(p);
                p = p->left;
            }

        }


        /** @return whether we have a next smallest number */
        bool hasNext() {
            return _next.size() != 0;
        }

        /** @return the next smallest number */
        int next() {
            if (!hasNext()) reurn 0;

            auto *p = _next.back();
            int val = p->val;
            _next.pop_back();
            
            p = p->right;
            while (p) {
                _next.push_back(p);
                p = p->left;
            }

            return val;
        }

    private:
        vector<TreeNode*> _next;
};

int main(int argc, char *argv[])
{
    {
        TreeNode n1 = {7};
        TreeNode n2 = {4};
        TreeNode n3 = {10};
        TreeNode n4 = {2};
        TreeNode n5 = {5};
        TreeNode n6 = {8};
        TreeNode n7 = {11};
        TreeNode n8 = {1};
        TreeNode n9 = {9};

        n1.left = &n2;
        n1.right = &n3;
        n2.left = &n4;
        n2.right = &n5;
        n3.left = &n6;
        n3.right = &n7;
        n4.left  = &n8;
        n6.right = &n9;

        BSTIterator i = BSTIterator(&n1);
        while (i.hasNext())
            cout << i.next() << " ";
        cout << endl;
    }
    {
        TreeNode n1 = {7};
        BSTIterator i = BSTIterator(&n1);
        while (i.hasNext())
            cout << i.next() << " ";
        cout << endl;
    }
    
    {
        BSTIterator i = BSTIterator(NULL);
        while (i.hasNext())
            cout << i.next() << " ";
        cout << endl;
    }
    return 0;
}
