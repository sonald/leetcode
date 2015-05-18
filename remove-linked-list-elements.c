/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode dummy = {0, head};
    struct ListNode** p = &dummy.next;
    while (*p) {
        if ((*p)->val == val) {
            *p = (*p)->next;
        } else {
            p = &(*p)->next;
        }
    }

    return dummy.next;
}