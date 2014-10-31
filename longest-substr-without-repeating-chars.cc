#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
    int lengthOfLongestSubstring(string s) {
        int c = 0, l = 0, max = 0;
        
        ::map<char, decltype(s.size())> h;
        auto sz = s.size();
        for (decltype(s.size()) i = 0; i < sz; ++i) {
            if (h.find(s[i]) == h.end() || h[s[i]] < c) {
                l++;
                h[s[i]] = i;
            } else {
                auto pre = h[s[i]];
                max = l > max ? l : max;
                l = i - pre;
                c = pre + 1;
                h[s[i]] = i;
                //cout << "pre: " << pre << " c: " << c << " i: " << i 
                    //<< " l: " << l << " max: " << max << endl;
            }
        }

        max = l > max ? l : max;
        return max;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << sol.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << sol.lengthOfLongestSubstring("aaaa") << endl;
    cout << sol.lengthOfLongestSubstring("a") << endl;
    
    //expect 12
    cout << sol.lengthOfLongestSubstring("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco") << endl;

}
