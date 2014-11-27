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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode* n = NULL) : val(x), next(n) {}
};

ostream& operator<<(ostream& os, ListNode* l)
{
    while (l) {
        os << l->val << " ";
        l = l->next;
    }

    return os << "$";
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
    TreeNode *sortedListToBST(ListNode *head) {
        vector<int> num;
        while (head) {
            num.push_back(head->val); head = head->next;
        }
        return sortedArrayToBST(num);
    }

    TreeNode *sortedArrayToBST(vector<int> &num) {
        return build(num, 0, num.size()-1);
    }

    TreeNode* build(vector<int>& num, int l, int r) {
        if (l > r) return NULL;

        int m = l + (r-l+1)/2;
        auto* t = new TreeNode {num[m]};
        t->left = build(num, l, m-1);
        t->right = build(num, m+1, r);
        return t;
    }
};

//O(n) time , O(lgn) space 
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        int n = 0;
        ListNode* p = head;
        while (p) { n++; p = p->next; }
        return helper(head, n);
    }

    TreeNode* helper(ListNode* &h, int n) {
        if (n == 0) return nullptr;
        auto* left = helper(h, n/2);
        auto* root = new TreeNode {h->val};
        h = h->next;
        root->left = left;
        root->right = helper(h, n - n/2 - 1);
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

void test(ListNode* l) {
    cout << l << endl;
	auto* t = Solution().sortedListToBST(l);
    dump(t);
	auto* t2 = Solution2().sortedListToBST(l);
    dump(t2);
}

ListNode* build_list(const vector<int>& v)
{
    ListNode* h = NULL, **p = &h;
    for (auto& x: v) {
        *p = new ListNode{x};
        p = &(*p)->next;
    }
    return h;
}

int main(int argc, char const *argv[])
{
    {
        vector<int> v {1,2,3,4,5,6,7,8};
        test(build_list(v));
    }
    {
        vector<int> v {1,2};
        test(build_list(v));
    }
    return 0;    
}
