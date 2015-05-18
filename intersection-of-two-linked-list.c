/**
 * Definition for singly-linked list.
 */

#include <stdio.h>
#include <stdlib.h>

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
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode* f = headA, *s = headB;
    if (!f || !s) return NULL;
    if (f == s) return f;

    int n1 = 0, n2 = 0;
    while (f->next) { f = f->next; n1++; }
    while (s->next) { s = s->next; n2++; }

    if (s != f) return NULL;

    struct ListNode* last = s;

    if (n1 < n2) {
        struct ListNode* tmp = headA;
        headA = headB;
        headB = tmp;
    }
    s->next = headB; // make a circle

    f = headA, s = headA;
    do {
        f = f->next;
        s = s->next->next;
    } while (f != s);

    f = headA;
    while (f != s) {
        f = f->next; s = s->next;
    }

    last->next = NULL;
    return f;
}

int main(int argc, char const *argv[])
{
    struct ListNode n = {2, 0};
    struct ListNode n2 = {3, 0};
    struct ListNode n3 = {4, 0};
    struct ListNode n4 = {5, 0};
    struct ListNode n5 = {6, 0};
    struct ListNode n6 = {7, 0};

    n.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;

    struct ListNode* nd = getIntersectionNode(&n2, &n);
    printf("%d\n", nd ? nd->val : -1);
    return 0;
}