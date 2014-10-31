#include <iostream>

using namespace std;
class Solution {
    public:
        bool isPalindrome(int x) {
            if (x < 0) return false;

            int y = x, rx = 0;
            while (y) {
                rx = rx * 10 + (y%10);
                y = y / 10;
            }

            return (rx == x);
        }
};

void test(int v)
{
    Solution sol;
    cerr << v << " == " << sol.isPalindrome(v) << endl;
}

int main(int argc, char *argv[])
{
    test(12321);
    test(0);
    test(-12466421);
    test(1807010401);
    test(-2147447412);
    return 0;
}
