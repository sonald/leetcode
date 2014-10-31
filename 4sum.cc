#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;
ostream& operator<<(ostream& os, vector<vector<int>> vvi)
{
    for (const auto& vi: vvi) {
        os << "<";
        for (auto i: vi) {
            os << i << ",";
        }
        os << ">" << endl;
    }

    return os;
}

class Solution {
    public:
        vector<vector<int> > fourSum(vector<int> &num, int target) {
            vector<vector<int>> vvi;
            auto n = num.size();
            if (n < 4) return vvi;

            std::sort(num.begin(), num.end());
            int i = 0, j, k, l;

            for (i = 0; i < n-3;) {
                for (j = i+1; j < n-2;) {
                    for (k = j+1, l = n-1; k < l;) {
                        auto v = num[i] + num[j] + num[k] + num[l];
                        if (v == target) {
                            vvi.push_back({num[i], num[j], num[k], num[l]});
                            auto tl = num[l], tk = num[k];
                            while (k < l && num[l] == tl) l--;
                            while (k < l && num[k] == tk) k++;

                        } else if (v > target) {
                            auto tl = num[l];
                            while (k < l && num[l] == tl) l--;
                        } else {
                            auto tk = num[k];
                            while (k < l && num[k] == tk) k++;
                        }
                    }

                    auto tj = num[j];
                    while (j <= n-2 && tj == num[j]) j++;
                }

                auto ti = num[i];
                while (i <= n-3 && ti == num[i]) i++;
            }

            return vvi;
        }
};

void test(const vector<int>& vs, int target)
{
    Solution sol;
    vector<int> vs2 {vs};
    cout << sol.fourSum(vs2, target) << endl;
}

int main(int argc, char *argv[])
{
    test({1,0,-1,0,-2,2}, 0);
    test({-1, -1, -1, -1, -1}, -4);
    test({ -1, -1, -1, -1}, -4);
    return 0;
}



