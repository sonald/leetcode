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
        os << n->val << " > ";
        n = n->next;
    }
    return os << endl;
}

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (!head) return head;
        
        ListNode * fast = head, * slow = head;
        for (int i = 0; i < k; ++i) {
            if (slow->next) slow = slow->next;
            else slow = head;
        }

        while (slow->next) {
            fast = fast->next;
            slow = slow->next;
        }

        // cout << fast->val <<"," << slow->val << endl;
        slow->next = head;
        head = fast->next;
        fast->next = NULL;
        return head;
    }
};

void test(ListNode *head, int k) {
	cout << Solution().rotateRight(head, k) << endl;
}

int main(int argc, char const *argv[])
{
    test(NULL, 2);
    for (int i = 0; i <=3; i++) {
        ListNode n {1};
        test(&n, i);
    }
    for (int i = 0; i <=3; i++) {
        ListNode n {1, new ListNode{2}};
        test(&n, i);
    }
    for (int i = 0; i <=5; i++) {
        ListNode n {1, new ListNode{2, new ListNode {3, new ListNode{4, new ListNode{5}}}}};
        test(&n, i);
    }
	return 0;
}