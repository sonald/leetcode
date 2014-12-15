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
        bool hasCycle(ListNode *head) {
            ListNode dummy {0};
            dummy.next = head;
            auto* fast = dummy.next, *slow = &dummy;
            while (fast && slow) {
                if (fast == slow) return true;
                fast = fast->next;
                if (fast) fast = fast->next;
                slow = slow->next;
            }

            return false;
        }
};

void test(ListNode* head)
{
    cout << Solution().hasCycle(head) << endl;
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
        ListNode h {4};
        auto* n1 = new ListNode {2};
        auto* n2 = new ListNode {1};
        h.next = n1;
        n1->next = n2;
        n2->next = &h;
        test(&h);
    }
    {
        ListNode h {2, new ListNode {1, new ListNode {5, new ListNode {4, new ListNode {3}}}}};
        test(&h);
    }
    return 0;
}



