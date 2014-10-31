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

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.size(), n2 = num2.size();
        string last;
        for (int i = n2-1; i >= 0; i--) {
            string r = calc(num1, num2[i], n2-i-1);
            if (last.size()) {
                last = add(last, r);
            } else last = r;
        }
        return last;
    }

    string add(string& s1, string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n1 == 1 && n2 == 1 && s1[0] == '0' && s2[0] == '0') return "0";

        string res = (n1 > n2) ? s1 : s2;
        int n = std::min(n1, n2), carry = 0, m = res.size();
        for (int i = 0; i < n; i++) {
            int k = s1[n1-1-i] + s2[n2-1-i] - '0' - '0' + carry;
            res[m-i-1] = k % 10 + '0';
            carry = k / 10;
        }

        n = m - n - 1;
        while (n >= 0) {
            int k = res[n] + carry - '0';
            res[n] = k % 10 + '0';
            carry = k / 10;
            n--;
        }
        if (carry) res = "1" + res;
        return res;
    }

    string calc(string& s, char ch, int shift) {
        if (ch == '0' || (s.size() == 1 && s[0] == '0')) return "0";

        string res(s.size()+1, '0');
        int carry = 0, m = res.size();
        for (int n = s.size(), i = 0; i < n; i++) {
            int k = (s[n-1-i]-'0') * (ch-'0') + carry;
            res[m-i-1] = k%10 + '0';
            carry = k / 10;
        }
        if (carry) res[0] = carry + '0';
        else res = res.substr(1);        
        return res + string(shift, '0');
    }

};

void test(string num1, string num2) {
    cout << Solution().multiply(num1, num2) << endl;
}

int main(int argc, char const *argv[])
{
    test("1111", "23"); // 2553
    test("9871", "83"); //819293 
    test("32923", "0"); // 0
    test("32923", "100"); // 3292300
    test("111111", "01"); 
    test("0", "3232"); // 0
    test("3010", "90201"); // 271505010
    test("123456789", "8923"); // 1101604928247
	return 0;
}