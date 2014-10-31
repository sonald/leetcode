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
        ListNode* swapPairs(ListNode *head) {
            if (!head) return NULL;

            ListNode* l1 = head, * l2 = head->next;
            ListNode* prev = NULL;
            if (!l1 || !l2) return head;
            head = NULL;

            while (l1 && l2) {
                l1->next = l2->next;
                l2->next = l1;
                if (prev) prev->next = l2;
                prev = l1;
                if (!head) head = l2;
                l1 = prev->next;
                if (l1)
                    l2 = l1->next;
            }

            return head;
        }
};

void test(ListNode* head)
{
    Solution sol;
    auto* l = sol.swapPairs(head);
    cout << l << endl;
}

int main(int argc, char *argv[])
{
    {
        ListNode h {
            1,
                new ListNode { 
                    2,
                    new ListNode {
                        3,
                        NULL
                    }
                }
        };
        test(&h);
    }
    {
        ListNode h {
            1,
                new ListNode { 
                    2,
                    new ListNode {
                        3,
                        new ListNode {
                            4,
                            NULL
                        }
                    }
                }
        };
        test(&h);
        test(NULL);
    }
    return 0;
}


