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
        ListNode *reverseKGroup(ListNode *head, int k) {
            if (k == 1) return head;

            ListNode* target = NULL, * r = NULL, * l = NULL, 
                * h = NULL, * t = NULL, * prev = NULL;
            
            while (1) {
                int count = 0;
                l = r = head;
                while (r && count < k) {
                    count++;
                    r = r->next;
                }
                if (count < k) break;

                h = t = NULL;
                while (l != r) {
                    ListNode* n = l;
                    l = l->next;

                    if (!t) t = n;
                    n->next = h;
                    h = n;
                }

                if (prev) prev->next = h;
                prev = t;
                if (!target) target = h;
                head = r;
            }

            if (head) {
                if (prev) prev->next = head;
                else if (!target) return head;
            }

            return target;
        }
};

void test(ListNode* head, int k)
{
    Solution sol;
    auto* l = sol.reverseKGroup(head, k);
    cout << l << endl;
}

int main(int argc, char *argv[])
{
    {
        ListNode h {
            1, NULL
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
                        NULL
                    }
                }
        };
        test(&h, 1);
    }
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
        test(&h, 2);
        //test(NULL);
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
        test(&h, 3);
        test(NULL, 2);
    }
    return 0;
}



