#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

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
        os << n->val << " -> ";
        n = n->next;
    }
    return os;
}

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        int len = n - m + 1;
        ListNode dummy(0);
        dummy.next = head;

        ListNode *p = &dummy, *q = &dummy;
        for (int i = 1; i <= n; i++) {
            q = q->next;
            if (i < m) p = p->next;
        }

        ListNode* h = q->next, *p1 = p->next;
        q->next = NULL;
        while (p1) {
            auto* x = p1;
            p1 = p1->next;

            x->next = h;
            h = x;
        }
        p->next = h;
        return dummy.next;
    }
};

void test(ListNode* head, int m, int n)
{
    Solution sol;
    auto* l = sol.reverseBetween(head, m, n);
    cout << l << endl;
}

int main(int argc, char *argv[])
{
    {
        ListNode h {1, NULL };
        test(&h, 1, 1);
    }
    {
        ListNode h {1, new ListNode {2, new ListNode {3, NULL } } };
        test(&h, 1, 2);
    }
    {
        ListNode h {1, new ListNode {2, new ListNode {3, NULL } } };
        test(&h, 2, 3);
    }

    {
        ListNode h {1, new ListNode {2, new ListNode {3, new ListNode {
                    4, NULL } } } };
        test(&h, 2, 4);
    }
    {
        ListNode h {1, new ListNode {2, new ListNode {3, new ListNode {
                    4, NULL } } } };
        test(&h, 1, 4);
    }
    return 0;
}



