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

template <class T, class U>
ostream& operator<<(ostream& os, const unordered_map<T, U>& v)
{
    os << "{";
    for (const auto& t: v) {
        os << "(" << t.first << ":" << t.second << ")";
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]\n";
}

class Solution {
    public:
        int evalRPN(vector<string> &tokens) {
            vector<int> sp;
            for (auto& s: tokens) {
                if (s == "+") {
                    auto v2 = sp.back(); sp.pop_back();
                    auto v1 = sp.back(); sp.pop_back();
                    sp.push_back(v1 + v2);
                } else if (s == "-") {
                    auto v2 = sp.back(); sp.pop_back();
                    auto v1 = sp.back(); sp.pop_back();
                    sp.push_back(v1 - v2);
                } else if (s == "*") {
                    auto v2 = sp.back(); sp.pop_back();
                    auto v1 = sp.back(); sp.pop_back();
                    sp.push_back(v1 * v2);
                } else if (s == "/") {
                    auto v2 = sp.back(); sp.pop_back();
                    auto v1 = sp.back(); sp.pop_back();
                    sp.push_back(v1 / v2);
                } else 
                    sp.push_back(std::atoi(s.c_str()));
            }
            return sp.back();
        }
};


void test(vector<string> tokens) {
    cout << Solution().evalRPN(tokens) << endl;
}

int main(int argc, char const *argv[])
{
    test({"2", "1", "+", "3", "*"}); // 9
    test({"4", "13", "5", "/", "+"}); // 6
    return 0;
}
