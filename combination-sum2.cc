#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]" << endl;
}

class Solution {
public:
    vector<vector<int>> res;
    std::vector<int> sp;

    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        solve(candidates, 0, target);
        return res;
    }

    void solve(std::vector<int>& candidates, int index, int target) {
        for (int i = index, n = candidates.size(); i < n; i++) {
            int p = candidates[i];

            sp.push_back(p);
            if (target - p > 0) {
                solve(candidates, i+1, target-p);
                while (i < n && candidates[i+1] == candidates[i]) i++;
            } else if (target == p) {
                res.push_back(sp);
                while (i < n && candidates[i+1] == candidates[i]) i++;                
            }  else {
                sp.pop_back();
                break;
            }
            sp.pop_back();
        }
    }
};

void test(vector<int> &candidates, int target) {
    Solution sol;
    cout << sol.combinationSum2(candidates, target) << endl;
}

int main(int argc, char *argv[])
{
    {
        std::vector<int> v {2, 3, 6, 7};
        test(v, 7);
    }
    {
        std::vector<int> v {1, 1};
        test(v, 1);
    }
    {
        std::vector<int> v {1, 1, 1, 1, 1, 1};
        test(v, 5);
    }
    {
        std::vector<int> v {2, 2, 3, 6, 7};
        test(v, 5);
    }
    {
        vector<int> v {10,1,2,7,6,1,5};
        test(v, 8);
    }
    {
        vector<int> v {10,1,2,7,6,1,5, 5};
        test(v, 8);
    }
    return 0;
}





