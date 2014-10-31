#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
    public:
        int threeSumClosest(vector<int> &num, int target) {
            int n = num.size();
            std::sort(num.begin(), num.end());
            int min = num[0] + num[1] + num[2],
                max = num[n-1] + num[n-2] + num[n-3];

            for (int i = 0; i < n-2; ++i) {
                for (int j = i+1, k = n-1; j < k;) {
                    auto v = num[i] + num[j] + num[k];
                    if (v == target)
                        return v;
                    else if (v > target) {
                        max = std::min(max, v);
                        auto tk = num[k];
                        while (j < k && tk == num[k]) k--;
                    } else {
                        min = std::max(min, v);
                        auto tj = num[j];
                        while (j < k && tj == num[j]) j++;
                    }
                }
            }

            cout << "min: " << min << ", max: " << max << endl;
            return (target - min > max - target) ? max : min;
        }
};

void test(const vector<int>& vs, int target)
{
    Solution sol;
    vector<int> vs2 {vs};
    cout << sol.threeSumClosest(vs2, target) << endl;

}

int main(int argc, char *argv[])
{
    //test({0, 1, 2}, 0);
    //test({0, 2, 1, -3}, 1);
    //test({-1, 2, 1, -4}, 1);
    //test({-4, -2, -1, 0, 1, 3, 5}, 3);
    //test({-4, -2, -1, 0, 1, 3, 5}, 7);
    // -274
    test({87,6,-100,-19,10,-8,-58,56,14,-1,-42,-45,-17,10,20,-4,13,-17,0,11,-44,65,74,-48,30,-91,13,-53,76,-69,-19,-69,16,78,-56,27,41,67,-79,-2,30,-13,-60,39,95,64,-12,45,-52,45,-44,73,97,100,-19,-16,-26,58,-61,53,70,1,-83,11,-35,-7,61,30,17,98,29,52,75,-73,-73,-23,-75,91,3,-57,91,50,42,74,-7,62,17,-91,55,94,-21,-36,73,19,-61,-82,73,1,-10,-40,11,54,-81,20,40,-29,96,89,57,10,-16,-34,-56,69,76,49,76,82,80,58,-47,12,17,77,-75,-24,11,-45,60,65,55,-89,49,-19,4}, -275);
    return 0;
}


