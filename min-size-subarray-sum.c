#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// sliding window algorithm O(n)
typedef struct {
    int l, r;
} range_t;

int minSubArrayLen(int s, int* nums, int n) {
    range_t r = {0, 0};
    if (n <= 0) return 0;

    int m = INT_MAX;
    int f = nums[0];
    while (r.l < n-1) {
        while (f < s && r.r < n-1) {
            f += nums[++r.r];
        }
        if (f >= s && m > r.r - r.l + 1) m = r.r - r.l + 1;

        f -= nums[r.l++];
        if (f >= s && m > r.r - r.l + 1) m = r.r - r.l + 1;
        if (r.l < n-1 && f == 0) {
            r.r = r.l;
            f = nums[r.r];
        }
    }

    if (m == INT_MAX) return 0;
    return m;
}

// contrive one with O(NlgN) complexity
int minSubArrayLen2(int s, int* nums, int n) {
    range_t r = {0, 0};
    if (n <= 0) return 0;

}

int main(int argc, char const *argv[])
{
    int a[] = {1,2,3,4,5};
    printf("%d\n", minSubArrayLen(11, a, 5));
    return 0;
}