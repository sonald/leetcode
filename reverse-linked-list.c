/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList1(struct ListNode* head) {
    struct ListNode* t = NULL, *p = head;
    while (p) {
        p = p->next;
        head->next = t;
        t = head;
        head = p;
    }

    return t;
}

// recursively
struct ListNode* reverseList2(struct ListNode* head) {
	if (!head) return NULL;
	if (!head->next) return head;

	struct ListNode* p = reverseList2(head->next);
	struct ListNode* q = p;
	while (p->next) p = p->next;
	p->next = head;
	head->next = NULL;
	return q;
}

static void helper(struct ListNode* head, struct ListNode** tail)
{
	if (!head) return;
	struct ListNode* p = head->next;
	head->next = *tail;
	*tail = head;
	helper(p, tail);
}

struct ListNode* reverseList3(struct ListNode* head) {
	struct ListNode* tail = NULL;
	helper(head, &tail);
	return tail;
}