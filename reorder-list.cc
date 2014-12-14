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
        void reorderList(ListNode *head) {
            if (!head) return;
            ListNode* front = head->next, *tail = head;
            while (front && front->next) {
                tail = tail->next;
                front = front->next;
                if (front) front = front->next;
            }

            auto* t = tail; 
            tail = tail->next;
            front = t->next = nullptr;
            while (tail) {
                t = tail;
                tail = tail->next;
                t->next = front;
                front = t;
            }

            //cout << "tail: " << front << endl;
            tail = head;
            while (front) {
                auto* t = front;
                front = front->next;
                t->next = tail->next;
                tail->next = t;
                tail = t->next;
            }
        }
};

void test(ListNode* head)
{
    Solution().reorderList(head);
    cout << head << endl;
}

int main(int argc, char *argv[])
{
    {
        ListNode h {1};
        test(&h);
    }
    {
        ListNode h {1, new ListNode {2, new ListNode {3, NULL } } };
        test(&h);
    }

    {
        ListNode h {1, new ListNode {2, new ListNode {3, new ListNode { 4}} } };
        test(&h);
    }
    {
        ListNode h {1, new ListNode {2, new ListNode {3, new ListNode {4, new ListNode {5}}}}};
        test(&h);
    }
    {
        ListNode h {1, new ListNode {2, new ListNode {3, new ListNode {4, new ListNode {5,
            new ListNode{6}}}}}};
        test(&h);
    }
    return 0;
}



