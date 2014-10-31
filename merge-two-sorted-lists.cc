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


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode* n = NULL) : val(x), next(n) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode dummy {0};
        ListNode** tail = &dummy.next;
        while (l1 && l2) {
            ListNode* tmp = nullptr;
            if (l1->val < l2->val) {
                tmp = l1; l1 = l1->next;
            } else {
                tmp = l2; l2 = l2->next;
            }
            *tail = tmp;
            tail = &tmp->next;
        }

        ListNode* tmp = l1 ? l1 : l2;
        while (tmp) {
            *tail = tmp;
            tmp = tmp->next;
            tail = &(*tail)->next;
        }
        return dummy.next;
    }
};

void mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode* ln = Solution().mergeTwoLists(l1, l2);
    while (ln) {
        cout << ln->val << " ";
        ln = ln->next;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    {
        ListNode n1 {
            1,
            new ListNode {
                5,
                new ListNode {
                    9,
                    new ListNode {10}
                }
            }
        };

        ListNode n2 {
            2,
            new ListNode {
                4,
                new ListNode {
                    8,
                    new ListNode {12}
                }
            }
        };
        mergeTwoLists(&n1, &n2);
    } 
	return 0;
}