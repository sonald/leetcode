/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    struct TreeNode* stack[1000];
    memset(stack, 0, sizeof stack);
    int sp = 0, sp2 = 0;

    struct TreeNode* stack2[1000];
    memset(stack2, 0, sizeof stack2);

    int res[1000] = {0, };
    int n = 0;

    struct TreeNode* *stk = stack;
    stk[sp++] = root;
    while (sp) {
        res[n++] = stk[sp-1]->val;
        sp2 = 0;
        struct TreeNode* *stk2 = (stk == stack) ? stack2: stack;
        for (int i = 0; i < sp; i++) {
            struct TreeNode* nd = stk[i];
            if (nd->left) stk2[sp2++] = nd->left;
            if (nd->right) stk2[sp2++] = nd->right;
        }
        sp = sp2;
        stk = stk2;
    }
    *returnSize = n;
    int* r = (int*)malloc(sizeof(int)*n);
    memcpy(r, res, sizeof(int)*n);
    return r;
}