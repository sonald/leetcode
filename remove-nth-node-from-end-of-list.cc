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
        ListNode *removeNthFromEnd2(ListNode *head, int n) {
            map<int, ListNode*> order;
            int i = 0;
            ListNode* p = head;
            while (p) {
                order.insert(std::make_pair(i++, p));
                p = p->next;
            }
            
            ListNode* d = order[i-n];
            if (i-n == 0) return d->next;
            else {
                ListNode* prev = order[i-n-1];
                prev->next = d->next;
            }
            return head;
        }

        // fast & slow pointer
        ListNode *removeNthFromEnd(ListNode *head, int n) {
            ListNode* fn = head, *sn = head;
            while (n--) fn = fn->next;
            if (!fn) return head->next;

            while (fn && fn->next) {
                fn = fn->next;
                sn = sn->next;
            }

            sn->next = sn->next->next;
            return head;
        }
};

void test(ListNode* head, int n)
{
    Solution sol;
    auto* l = sol.removeNthFromEnd(head, n);
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
        test(&h, 2);
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
        test(&h, 4);
    }
    return 0;
}



