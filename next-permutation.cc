#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

template<class T>
ostream& operator<<(ostream& os, vector<T>& v)
{
    for (auto& t: v) {
        cout << t << " ";
    }
    return cout;
}

class Solution {
    public:
        void nextPermutation(vector<int> &num) {
            for (int n = num.size(), i = n-2; i >= 0; --i) {
                if (num[i] < num[i+1]) {
                    int j = i+1;
                    while (j < n && num[j] > num[i]) ++j;
                    std::swap(num[i], num[j-1]);
                    std::sort(num.begin()+i+1, num.end());
                    return;
                }
            }

            // reverse
            for (int i = 0, j = num.size()-1; i < j; ++i, --j) {
                std::swap(num[i], num[j]);
            }
        }
};

void test(vector<int> &num)
{
    cout << num << " -> ";
    cout.flush();
    Solution sol;
    sol.nextPermutation(num);
    cout << num << endl;
}

int main(int argc, char *argv[])
{
    {
        vector<int> v {1,3,2};
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
    }
    {
        vector<int> v {1,1,5};
        test(v);
    }
    {
        vector<int> v {2,4,3,1};
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
        test(v);
    }
    return 0;
}
// 1 4 3 2 -> 2 1 3 4
// 2 1 4 3 5 -> 2 3 1 4 5