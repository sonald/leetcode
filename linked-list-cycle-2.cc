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

class Solution2 {
    public:
        ListNode* detectCycle(ListNode *head) {
            ListNode dummy {0};
            dummy.next = head;
            auto* fast = dummy.next, *slow = &dummy;
            while (fast && fast->next) {
                if (fast == slow) {
                    while (fast->next != slow) {
                        head = dummy.next;
                        while (head != slow) {
                            if (fast->next == head) return head;
                            head = head->next;
                        }
                        fast = fast->next;
                    }
                    return slow;
                }
                fast = fast->next->next;
                slow = slow->next;
            }

            return nullptr;
        }
};

// OJ disobey changing of orignal list
class Solution {
    public:
        ListNode* detectCycle(ListNode *head) {
            ListNode dummy {0};
            dummy.next = head;
            auto* fast = dummy.next, *slow = &dummy;
            while (fast && slow) {
                if (fast == slow) {
                    while (head->next) {
                        auto* t = head;
                        head = head->next;
                        t->next = nullptr;
                    }
                    return head;
                }
                fast = fast->next;
                if (fast) fast = fast->next;
                slow = slow->next;
            }

            return nullptr;
        }
};

void test(ListNode* head)
{
   auto* l = Solution2().detectCycle(head);
   cout << (l?l->val:0) << endl; 
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
        ListNode h {1};
        auto* n1 = new ListNode {2};
        auto* n2 = new ListNode {3};
        auto* n3 = new ListNode {4};
        h.next = n1;
        n1->next = n2;
        n2->next = n3;
        n3->next = &h;
        test(&h);
    }
    {
        ListNode h {1};
        auto* n1 = new ListNode {2};
        auto* n2 = new ListNode {3};
        auto* n3 = new ListNode {4};
        h.next = n1;
        n1->next = n2;
        n2->next = n3;
        n3->next = n1;
        test(&h);
    }
    {
        ListNode h {1};
        auto* n1 = new ListNode {2};
        auto* n2 = new ListNode {3};
        auto* n3 = new ListNode {4};
        h.next = n1;
        n1->next = n2;
        n2->next = n3;
        n3->next = n2;
        test(&h);
    }

    {
        ListNode h {1};
        auto* n1 = new ListNode {2};
        auto* n2 = new ListNode {3};
        auto* n3 = new ListNode {4};
        h.next = n1;
        n1->next = n2;
        n2->next = n3;
        n3->next = n3;
        test(&h);
    }
    return 0;
}



