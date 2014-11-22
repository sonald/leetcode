#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

template<class T, class S>
ostream& operator<<(ostream& os, const unordered_map<T, S>& v)
{
	bool f = true;
	os << "{";
    for (auto& t: v) {
    	if (f) os << "(" << t.first << "," << t.second << ")";
    	else os << "," << "(" << t.first << "," << t.second << ")";
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vs)
{
	os << "[";
    for (auto& s: vs) {
        os << s << " ";
    }
    return os <<"]";
}

class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if (n == 0) return 0;

        std::vector<int> dp(n+1, 1);
        dp[n-1] = s[n-1] == '0' ? 0 : 1;
        for (int j = n - 2; j >= 0; j--) {
            dp[j] = s[j+1] == '0' ? 0: dp[j+1];
            auto v = std::stoi(s.substr(j, 2));
            if (s[j+1] == '0' && (v == 0 || v >= 30)) {
                return 0;
            }
            if (v > 0 && v <= 26 && j+2 <= n) {
                dp[j] += dp[j+2];
            }
        }

        return s[0] == '0' ? 0 : dp[0];
    }
};

void test(string n) {
    cout << Solution().numDecodings(n) << endl;
}

int main(int argc, char const *argv[])
{
    test("");  // 0
    test("0"); // 0
    test("03"); // 0 this considers invalid
    test("30"); // 0
    test("3030"); // 0
    test("3020"); // 0
    test("2030"); // 0
    test("20301"); // 0
    test("10011"); // 0
    test("124048111");  // 0

    cout << "-------------\n";

    test("101"); // 1
    test("3"); // 1
    test("32"); // 1
    test("12"); // 2
    test("12925");  // 4
    test("1111"); // 5
    test("1101"); // 3
    return 0;
}