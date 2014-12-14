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
        ListNode *insertionSortList(ListNode *head) {
            ListNode dummy {INT_MIN};
            while (head) {
                auto* t = head;
                head = head->next;
                auto *p = &dummy;
                while (p->next && p->next->val < t->val) {
                    p = p->next;
                }
                t->next = p->next;
                p->next = t;
            }

            return dummy.next;
        }
};

void test(ListNode* head)
{
    cout << Solution().insertionSortList(head) << endl;
}

int main(int argc, char *argv[])
{
    {
        ListNode h {1};
        test(&h);
    }
    {
        ListNode h {3, new ListNode {2, new ListNode {1, NULL } } };
        test(&h);
    }

    {
        ListNode h {4, new ListNode {2, new ListNode {1, new ListNode { 3}} } };
        test(&h);
    }
    {
        ListNode h {2, new ListNode {1, new ListNode {5, new ListNode {4, new ListNode {3}}}}};
        test(&h);
    }
    {
        ListNode h {6, new ListNode {2, new ListNode {1, new ListNode {3, new ListNode {5,
            new ListNode{4}}}}}};
        test(&h);
    }
    return 0;
}



