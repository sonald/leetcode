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
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int carry = 0;
        ListNode *p = NULL,  **r = NULL;

        r = &p;
        while (l1 || l2) {
            auto val = 0;
            if (!l1) {
                val = l2->val + carry;
                l2 = l2->next;
            } else if (!l2) {
                val = l1->val + carry;
                l1 = l1->next;
            } else {
                val = l1->val + l2->val + carry;
                l1 = l1->next;
                l2 = l2->next;
            }
            carry = val >= 10;
            *r = new ListNode {carry?val-10:val};
            r = &(*r)->next;
        }

        if (carry) {
            *r = new ListNode {1};
        }
        return p;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    ListNode l1{9};
    ListNode l2{4};
    ListNode l3{3};
    l1.next = &l2; l2.next = &l3;

    ListNode l4{5};
    ListNode l5{6};
    ListNode l6{8};
    ListNode l7{2};
    l4.next = &l5; l5.next = &l6;
    l6.next = &l7;

    ListNode* r = sol.addTwoNumbers(&l1, &l4);
    while (r) {
        cout << r->val; 
        r = r->next;
    }
    cout << endl;
}
