#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;
class Solution{
    public:
        int reverse(int x) {
            int minus = x < 0;
            int abs = x>0?x:-x;
            int res = 0;
            while (abs) {
                res = res * 10 + (abs%10);
                abs /= 10;
            }

            return minus?-res:res;
        }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << sol.reverse(321) << endl;
    cout << sol.reverse(-23) << endl;
    cout << sol.reverse(-100030) << endl;
    return 0;
}
