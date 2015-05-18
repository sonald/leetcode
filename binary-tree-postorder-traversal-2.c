#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definition for a binary tree node.
 */
 typedef struct TreeNode {

      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  } TreeNode;



/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        result NULL;
    }

    TreeNode* stack1[1000]; //tmp
    TreeNode* stack2[1000]; //result
    memset(stack1, 0, sizeof stack1);
    memset(stack2, 0, sizeof stack2);

    int sp = 0, res = 0;

    stack1[sp++] = root;
    while (sp) {
        TreeNode* nd = stack1[sp-1];
        if ((res && nd->right == stack2[res-1])) {
            sp--;
            stack2[res++] = nd;
        } else if ((res && nd->left == stack2[res-1]) || nd->left == 0) {
            if (nd->right) {
                stack1[sp++] = nd->right;
            } else {
                sp--;
                stack2[res++] = nd;
            }
        } else {
            if (nd->left) stack1[sp++] = nd->left;
        }
    }

    *returnSize = res;
    int* result = (int*)malloc(sizeof(int)*res);
    for (int i = 0; i < res; i++) {
        result[i] = stack2[i]->val;
        printf("%d ", result[i]);
    }
    putchar('\n');
    return result;
}

void post(TreeNode* nd)
{
    if (!nd) return;
    post(nd->left);
    post(nd->right);
    printf("%d\n", nd->val);
}

int main(int argc, char *argv[])
{
    TreeNode n1 = {1, 0, 0};
    TreeNode n2 = {2, 0, 0};
    TreeNode n3 = {3, 0, 0};
    TreeNode n4 = {4, 0, 0};
    TreeNode n5 = {5, 0, 0};
    TreeNode n6 = {6, 0, 0};

    n1.left = &n2;
    n1.right = &n6;
    n2.right = &n3;
    n3.left = &n4;
    n3.right = &n5;

    int sz = 0;
    postorderTraversal(&n1, &sz);
    return 0;
}