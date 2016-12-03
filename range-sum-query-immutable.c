#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define VERSION 3
#if VERSION == 0
// baseline
struct NumArray {
    int *data;
    int sz;
};

struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    struct NumArray *na = (struct NumArray*)malloc(sizeof(struct NumArray));
    na->data = (int*)malloc(sizeof(int)*numsSize);
    memcpy(na->data, nums, sizeof(int)*numsSize);
    na->sz = numsSize;
    return na;
}

int sumRange(struct NumArray* numArray, int i, int j) {
    int r = 0;
    for (; i <= j; i++) {
        r += numArray->data[i];
    }
    return r;
}

void NumArrayFree(struct NumArray* numArray) {
    free(numArray->data);
    free(numArray);
}

#elif VERSION == 1
typedef struct Node {
    int l, r; // range
    int sum;
    struct Node *lhs, *rhs;
} Node;

struct NumArray {
    Node *root;
};


static Node* buildTree(int *nums, int sz, int l, int r)
{
    Node *nd = (Node*)malloc(sizeof(Node));
    memset(nd, 0, sizeof *nd);

    nd->l = l;
    nd->r = r;
    if (l < r) {
        int m = l + (r-l)/2;
        nd->lhs = buildTree(nums, sz, l, m);
        nd->rhs = buildTree(nums, sz, m+1, r);
        nd->sum = nd->lhs->sum + nd->rhs->sum;
    } else {
        nd->sum = nums[l];
        nd->lhs = nd->rhs = 0;
    }
    return nd;
}

struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    struct NumArray *na = (struct NumArray*)malloc(sizeof(struct NumArray));
    na->root = buildTree(nums, numsSize, 0, numsSize-1);
    return na;
}

static int sumRangeHelper(Node *nd, int i, int j) {
    if (nd->l == i && nd->r == j) {
        return nd->sum;
    }
    if (j <= nd->lhs->r) {
        return sumRangeHelper(nd->lhs, i, j);
    } else if (i >= nd->rhs->l) {
        return sumRangeHelper(nd->rhs, i, j);
    } else {
        return sumRangeHelper(nd->lhs, i, nd->lhs->r) + 
        sumRangeHelper(nd->rhs, nd->rhs->l, j);
    }
}

int sumRange(struct NumArray* numArray, int i, int j) {
    return sumRangeHelper(numArray->root, i, j);
}

void NumArrayFree(struct NumArray* numArray) {
    free(numArray);
}

#elif VERSION == 2
struct NumArray {
    int *sums;
    int sz;
};

struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    struct NumArray *na = (struct NumArray*)malloc(sizeof(struct NumArray));
    na->sz = numsSize + 1;
    na->sums = (int*)malloc(sizeof(int)*na->sz);
    na->sums[0] = 0;
    for (int i = 1; i < na->sz; i++) {
        na->sums[i] = nums[i-1] + na->sums[i-1];
    }
    return na;
}

int sumRange(struct NumArray* numArray, int i, int j) {
    return numArray->sums[j+1] - numArray->sums[i];
}

void NumArrayFree(struct NumArray* numArray) {
    free(numArray->sums);
    free(numArray);
}
#else
// fenwick tree
struct NumArray {
    int *tree;
    int sz;
};

struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    struct NumArray *na = (struct NumArray*)malloc(sizeof(struct NumArray));
    na->sz = numsSize;
    na->tree = (int*)malloc(sizeof(int)*na->sz);
    memset(na->tree, 0, sizeof(int)*na->sz);

    na->tree[0] = nums[0];
    for (int i = 1; i < na->sz; i++) {
        int l = i - (i & -i) + 1, r = i;
        for (; l <= r; l++) {
            na->tree[i] += nums[l]; 
        }
    }
    return na;
}

static int prefixSum(struct NumArray *numArray, int idx)
{
    int sum = 0;
    while (idx) {
        sum += numArray->tree[idx];
        idx -= idx & -idx;
    }

    return sum + numArray->tree[0];
}

int sumRange(struct NumArray* numArray, int i, int j) {
    if (i > 0)
        return prefixSum(numArray, j) - prefixSum(numArray, i-1);
    else
        return prefixSum(numArray, j);
}

void NumArrayFree(struct NumArray* numArray) {
    free(numArray->tree);
    free(numArray);
}

#endif

int sum(int *data, int i, int j) {
    int r = 0;
    for (; i <= j; i++) {
        r += data[i];
    }
    return r;
}

int main(int argc, char *argv[])
{
    // Your NumArray object will be instantiated and called as such:

    {
        int nums[] = {-2, 0, 3, -5, 2, -1};
        int numsSize = sizeof(nums)/sizeof(nums[0]);

        struct NumArray* numArray = NumArrayCreate(nums, numsSize);

        printf("%d\n", sumRange(numArray, 0, 2));
        printf("%d\n", sumRange(numArray, 2, 5));
        printf("%d\n", sumRange(numArray, 0, 5));

        NumArrayFree(numArray);
    }


    {
        int numsSize = 10000;
        int nums[numsSize];

        for (int i = 0; i < numsSize; i++) 
            nums[i] = rand() % 5000;

        struct NumArray* numArray = NumArrayCreate(nums, numsSize);

        for (int i = 0; i < 10000; i++) {
            int l = rand() % numsSize, r = (l + 1000) % numsSize;
            if (l > r) {int t = l; l = r; r = t;}
            /*printf("%d-%d: %d\n", l, r, sumRange(numArray, l, r));*/
            assert(sum(nums, l, r) == sumRange(numArray, l, r));
        }

        NumArrayFree(numArray);
    }
    return 0;
}

