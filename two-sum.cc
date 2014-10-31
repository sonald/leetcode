#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        vector<int> twoSum(vector<int> &numbers, int target) {
            map<int, int> h;
            for(int i = 0, sz = numbers.size(); i < sz; ++i) {
                h[numbers[i]] = i+1;
            }

            for(int i = 0, sz = numbers.size(); i < sz; ++i) {
                auto v = numbers[i], u = target - v;
                auto p = h.find(u);
                if (p != h.end() && p->second != i+1) {
                    return {i+1, h[u]};
                }
            }

            return {0, 0};
        }

};

int main(int argc, char *argv[])
{
    vector<int> v {2,7,11,15};
    vector<int> v3 {3,2,4};
    
    ::default_random_engine dre;
    ::uniform_int_distribution<int> di{1, 100000};
    vector<int> v2(100000);
    for(auto& x: v2) {
        x = di(dre);
    }


    cout << "size: " << v2.size() << endl;
    auto r = Solution().twoSum(v2, 102);
    cout << r[0] << r[1] << endl;

    Solution().twoSum(v, 102);

    auto r3 = Solution().twoSum(v3, 6);
    cout << r3[0] << r3[1] << endl;
    return 0;
}
