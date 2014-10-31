#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

/**
 *  * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode* n = NULL) : val(x), next(n) {}
};

ostream& operator<<(ostream& os, ListNode* ln)
{
    while (ln) {
        os << ln->val << " -> ";
        ln = ln->next;
    }
    return os;
}
 
class Solution {
    public:
        using Node = pair<int, ListNode*>;

        struct Comprare {
            int operator()(const Node& n1, const Node& n2) {
                return std::less<int>()(n2.second->val, n1.second->val);
            };
        };

        ListNode *mergeKLists(vector<ListNode *> &lists) {
            ListNode dummy {0};
            ListNode* ln = &dummy;

            std::priority_queue<Node, vector<Node>, Comprare> pq;
            for (int i = 0; i < lists.size(); ++i) {
                if (lists[i]) {
                    pq.emplace(i, lists[i]);
                    lists[i] = lists[i]->next;
                }
            }

            while (!pq.empty()) {
                ln->next = pq.top().second;
                int order = pq.top().first;
                ln = ln->next;
                ln->next = NULL;
                cout << "pop " << order << ", " << ln->val << endl;
                pq.pop();
                if (lists[order]) {
                    pq.emplace(order, lists[order]);
                    lists[order] = lists[order]->next;
                }
            }
            return dummy.next;
        }
};


void test(vector<ListNode *> &lists)
{
    Solution sol;
    cout << sol.mergeKLists(lists) << endl;
}

int main(int argc, char *argv[])
{
    {
        ListNode h1 {
            1,
            new ListNode {
                4,
                new ListNode {
                    10
                }
            }
        };

        ListNode h2 {
            2,
            new ListNode {
                3,
                new ListNode {
                    8,
                    new ListNode {
                        17
                    }
                }
            }
        };

        vector<ListNode*> vn;
        vn.push_back(&h1);
        vn.push_back(&h2);
        test(vn);
    }
    return 0;
}



