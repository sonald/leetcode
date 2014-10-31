#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const vector<vector<int>>& vvi)
{
    for (auto& vi: vvi) {
        cout << "[";
        for (auto i: vi) {
            cout << i << " ";
        }
        cout << "] ";
    }
    return os;
}

class Solution {
    public:
        vector<vector<int> > permute(vector<int> &num) {
            vector<vector<int>> ret;
            if (num.size() == 1) {
                ret.push_back({num[0]});
                return ret;
            }

            for (int i = 0; i < num.size(); ++i) {
                auto rx = num.begin() + i;
                int x = *rx;
                num.erase(rx);
                auto vvi = permute(num);
                for (auto&& vi: vvi) {
                    vi.insert(vi.begin(), x);
                    ret.push_back(vi);
                }
                num.insert(rx, x);
            }
            return ret;
        }

        vector<vector<int>> permuteRecurse(const vector<int>& num) {
        }
};

void test(vector<int> &num) 
{
    Solution sol;
    cout << sol.permute(num) << endl;
}

int main(int argc, char *argv[])
{
    {
        vector<int> vi {1};
        test(vi);
    }
    {
        vector<int> vi {1,2,3, 4};
        test(vi);
    }
    return 0;
}

