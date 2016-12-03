#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define VERSION 3

#if VERSION == 1
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

static void updateHelper(Node *nd, int i, int val) {
    if (nd->l == i && nd->r == i) {
        nd->sum = val;
        return;
    }

    if (i <= nd->lhs->r) {
        nd->sum -= nd->lhs->sum;
        updateHelper(nd->lhs, i, val);
        nd->sum += nd->lhs->sum;
    } else {
        nd->sum -= nd->rhs->sum;
        updateHelper(nd->rhs, i, val);
        nd->sum += nd->rhs->sum;
    }
}

void update(struct NumArray* numArray, int i, int val) {
    updateHelper(numArray->root, i, val);
}

void NumArrayFree(struct NumArray* numArray) {
    free(numArray);
}

#elif VERSION == 2

struct NumArray {
    int *tree;
    int len; // size of tree
    int sz; // size of nums
};

struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    struct NumArray *na = (struct NumArray*)malloc(sizeof(struct NumArray));
    na->sz = numsSize;

    int d = 1;
    while (numsSize >> d++);
    na->len = d << 1;
    na->tree = (int*)malloc(sizeof(int)*na->len);


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

static void updateHelper(Node *nd, int i, int val) {
    if (nd->l == i && nd->r == i) {
        nd->sum = val;
        return;
    }

    if (i <= nd->lhs->r) {
        nd->sum -= nd->lhs->sum;
        updateHelper(nd->lhs, i, val);
        nd->sum += nd->lhs->sum;
    } else {
        nd->sum -= nd->rhs->sum;
        updateHelper(nd->rhs, i, val);
        nd->sum += nd->rhs->sum;
    }
}

void update(struct NumArray* numArray, int i, int val) {
    updateHelper(numArray->root, i, val);
}

void NumArrayFree(struct NumArray* numArray) {
    free(numArray);
}

#else
// fenwick tree
struct NumArray {
    int *tree;
    int sz;
};

// this is how to read nums[idx-1] from tree without nums
static int getSingle(struct NumArray *numArray, int idx)
{
    int sum = numArray->tree[idx];
    if (idx > 0) {
        int z = idx - (idx & -idx);
        idx--;
        while (idx != z) {
            sum -= numArray->tree[idx];
            idx -= idx & -idx;
        }
    }

    return sum;
}

static int prefixSum(struct NumArray *numArray, int idx)
{
    int sum = 0;
    while (idx) {
        sum += numArray->tree[idx];
        idx -= idx & -idx;
    }

    return sum;
}

struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    struct NumArray *na = (struct NumArray*)malloc(sizeof(struct NumArray));
    na->sz = numsSize + 1;
    na->tree = (int*)malloc(sizeof(int)*na->sz);
    memset(na->tree, 0, sizeof(int)*na->sz);

    for (int i = 1; i < na->sz; i++) {
        int l = i - (i & -i) + 1, r = i;
        /*fprintf(stderr, "%d -> (%d %d) = ", i, l, r);*/
        for (; l <= r; l++) {
            na->tree[i] += nums[l-1]; 
        }
        /*fprintf(stderr, "%d\n", na->tree[i]);*/
    }

    for (int i = 1; i < na->sz; i++) {
        assert(getSingle(na, i) == nums[i-1]);
    }
    return na;
}

int sumRange(struct NumArray* numArray, int i, int j) {
    i++, j++;
    int v = prefixSum(numArray, j) - prefixSum(numArray, i-1);
    return v;
}

void update(struct NumArray* numArray, int i, int val) {
    i++;
    int delta = val - (prefixSum(numArray, i) - prefixSum(numArray, i-1));
    while (i < numArray->sz) {
        numArray->tree[i] += delta;
        i += i & -i;
    }
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
        int nums[] = {1, 3, 5};
        int numsSize = sizeof(nums)/sizeof(nums[0]);

        struct NumArray* numArray = NumArrayCreate(nums, numsSize);
        /*
         * sumRange(0, 2) -> 9
         * update(1, 2)
         * sumRange(0, 2) -> 8
         * */

        printf("%d\n", sumRange(numArray, 0, 2));
        update(numArray, 1, 2);
        printf("%d\n", sumRange(numArray, 0, 2));

        NumArrayFree(numArray);
    }

    {
        int numsSize = 10000;
        int nums[numsSize];

        for (int i = 0; i < numsSize; i++) 
            nums[i] = rand() % 5000;

        struct NumArray* numArray = NumArrayCreate(nums, numsSize);

        for (int i = 0; i < 100; i++) {
            int d = rand() % numsSize;
            int v = rand() % 5000;
            update(numArray, d, v);
            nums[d] = v;
        }

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

