#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode* n = NULL) : val(x), next(n) {}
};


ostream& operator<<(ostream& os, ListNode* n)
{
    while (n) {
        os << n->val << " > ";
        n = n->next;
    }
    return os;
}

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        auto* p = head;
        ListNode* pre = nullptr;
        bool dup = false;
        while (p) {
            if (p->next && p->next->val == p->val) {
                if (pre) { 
                    pre->next = p->next;
                    p = pre->next;
                } else { p = p->next; head = p; }
                dup = true;
            } else {
                if (dup) {
                    if (pre) {
                        pre->next = p->next;
                        p = pre->next;
                    } else { p = p->next; head = p; }
                    dup = false;
                } else {
                    pre = p;
                    p = p->next;
                }
            }
        }

        return head;
    }
};

void test(ListNode *head) {
	cout << Solution().deleteDuplicates(head) << endl;
}

int main(int argc, char const *argv[])
{
    test(NULL);
    {
        ListNode n {1, new ListNode{1, new ListNode {2, new ListNode{4, new ListNode{4}}}}};
        test(&n);
    }
    {
        ListNode n {2, new ListNode{2, new ListNode {2, new ListNode{2, new ListNode{3}}}}};
        test(&n);
    }
    {
        ListNode n {1, new ListNode{2, new ListNode {2, new ListNode{4, new ListNode{5}}}}};
        test(&n);
    }
	return 0;
}