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
    ListNode *partition(ListNode *head, int x) {
        if (!head || !head->next) return head;
        ListNode dummy {x-1};
        dummy.next = head;

        ListNode* i = &dummy, *p = &dummy;
        while (i->next && i->next->val < x) { i = i->next; p = i; }        
        while (p->next) {
            while (p->next && p->next->val >= x) p = p->next;
            if (p->next) {
                ListNode* l = p->next;
                p->next = l->next;
                l->next = i->next;
                i->next = l;
                i = l;
            }
        }        

        return dummy.next;
    }
};

void test(ListNode *head, int x) {
	cout << Solution().partition(head, x) << endl;
}

int main(int argc, char const *argv[])
{
    test(NULL, 0);
    {
        ListNode n {1, new ListNode{4, new ListNode {3, new ListNode{2, 
            new ListNode{5, new ListNode{2}}}}}};
        test(&n, 3); // 1->2->2->4->3->5
    }
    {
        ListNode n {2};
        test(&n, 1); // 2
    }
    {
        ListNode n {6, new ListNode{4, new ListNode {3, new ListNode{2, 
            new ListNode{5, new ListNode{2}}}}}};
        test(&n, 3);
    }
	return 0;
}