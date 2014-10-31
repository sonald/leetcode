#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (const auto& t: v) {
        os << t << " ";
    }
    return os << "]";
}

class Solution {
public:
    string countAndSay(int n) {
        string s("1");
        if (n == 1) return s;
        n--;
        while (n) {
            string ss;
            int ch = s[0], t = 1;
            for (int i = 1, m = s.size(); i < m; ++i) {
                if (s[i] == ch) t++;
                else {
                    ss += sayit(ch, t);
                    ch = s[i];
                    t = 1;
                }
            }
            ss += sayit(ch, t);            
            s = ss;
            n--;
        }

        return s;
    }

    string sayit(int ch, int count) {
        int map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};      
        string s;
        s += map[count];
        s += ch;
        return s;
    }
};

void test(int n)
{
    Solution sol;
    cout << sol.countAndSay(n) << endl;
}

int main(int argc, char *argv[])
{
    // 1, 11, 21, 1211, 111221, ...
    test(1);
    test(2);
    test(3);
    test(4);
    test(5);
    test(6);
    return 0;
}





