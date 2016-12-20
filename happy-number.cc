#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    // digits squared sum
    int dss(int n) {
        int s = 0;
        do {
            int r = n % 10;
            s += r * r;
            n = n / 10;
        } while (n);
        return s;
    }

    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = dss(slow);
            fast = dss(dss(fast));
        } while (slow != fast);

        return slow == 1;
    }
};

class Solution2 {
public:
    bool isHappy(int n) {
        unordered_set<int> m;

        while (n != 1) {
            int s = 0;
            do {
                int r = n % 10;
                s += r * r;
                n = n / 10;
            } while (n);

            if (m.find(s) != m.end())
                return false;
            m.insert(s);
            n = s;
        }

        return true;
    }
};

int main(int argc, char *argv[])
{
    
    cout << Solution().isHappy(19) << endl; // 1
    cout << Solution().isHappy(18) << endl; // 0
    return 0;
}
