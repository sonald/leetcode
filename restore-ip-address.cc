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
    std::vector<string> res;
    std::vector<int> sp; // end points
    vector<string> restoreIpAddresses(string s) {
        helper(s, 0, 4);
        return res;
    }

    void helper(string s, int i, int k) {
        if (k == 0) {
            if (i < s.size()) return;
            string x = s.substr(0, sp[0]) + '.' + s.substr(sp[0], sp[1] - sp[0]) + "." 
                + s.substr(sp[1], sp[2] - sp[1]) + "."+ s.substr(sp[2], sp[3] - sp[2]);
            res.push_back(x);
            return;
        }
        if (i+1 > s.size()) return;
        sp.push_back(i+1);
        helper(s, i+1, k-1);
        sp.pop_back();
        if (s[i] == '0') return;

        if (i+2 > s.size()) return;
        sp.push_back(i+2);
        helper(s, i+2, k-1);
        sp.pop_back();

        if (i+3 > s.size()) return;
        auto v = std::stoi(s.substr(i, 3));
        if (v <= 255) {
            sp.push_back(i+3);
            helper(s, i+3, k-1);
            sp.pop_back();
        }
    }
};

void test(string n) {
    cout << Solution().restoreIpAddresses(n) << " ";
    cout << endl;    
}

int main(int argc, char const *argv[])
{
    test("25525511135"); // ["255.255.11.135", "255.255.111.35"]
    test("01125324"); // 
    test("1111");
    test("25501234");
    return 0;
}