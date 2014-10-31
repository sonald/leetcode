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

    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        auto e = std::unique(candidates.begin(), candidates.end());
        while (e != candidates.end()) {
            e = candidates.erase(e);
        }
        // cout << "candidates: " << candidates << endl;
        solve(candidates, 0, target);
        return res;
    }

    void solve(std::vector<int>& candidates, int index, int target) {
        for (int i = index, n = candidates.size(); i < n; i++) {
            int p = candidates[i];
            sp.push_back(p);
            if (target - p > 0) {
                solve(candidates, i, target-p);
            } else if (target == p) {
                res.push_back(sp);
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
    cout << sol.combinationSum(candidates, target) << endl;
}

int main(int argc, char *argv[])
{
    {
        std::vector<int> v {2, 3, 6, 7};
        test(v, 7);
    }
    {
        std::vector<int> v {1, 1, 1, 1, 1, 1, 1, 1, 1};
        test(v, 5);
    }
    {
        std::vector<int> v {2, 2, 3, 6, 7};
        test(v, 7);
    }
    return 0;
}





