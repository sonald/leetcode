#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
        string longestCommonPrefix(vector<string> &strs) {
            string out;
            if (strs.size() == 0) return out;

            int l = 0;
            while (1) {
                if (l >= strs[0].size()) break;
                char pivot = strs[0][l];
                int i = 0;
                for (; i < strs.size(); i++) {
                    if (l >= strs[i].size()) break;
                    if (pivot != strs[i][l])
                        break;
                }

                if (i == strs.size()) out += pivot;
                else break;
                l++;
            }

            return out;
        }
};

void test(const vector<string>& vs)
{
    Solution sol;
    vector<string> vs2 {vs};
    cout << sol.longestCommonPrefix(vs2) << endl;
}

int main(int argc, char *argv[])
{
    test({"abc", "adc"});
    test({});
    test({"abc", "abd"});

    return 0;
}
