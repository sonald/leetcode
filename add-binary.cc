#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int carry = 0, i, j;
        for (i = a.size()-1, j = b.size()-1; i >= 0 && j >= 0; --i, --j) {
            int k = a[i] + b[j] - '0'*2 + carry;
            res.insert(res.begin(), (k%2) + '0');
            carry = k/2;
        }        

        string* s = i < 0 ? (i = j, &b): &a;
        while (i >= 0) {
            int k = (*s)[i] - '0' + carry;
            res.insert(res.begin(), (k%2 + '0'));
            carry = k/2;
            i--;
        }
        if (carry) res.insert(res.begin(), (carry + '0'));
        return res;
    }
};

void test(string a, string b) {
    cout << Solution().addBinary(a, b) << endl;
}

int main(int argc, char const *argv[])
{
    test("1", "0");
    test("11", "1");
    test("111", "1111");
    return 0;
}