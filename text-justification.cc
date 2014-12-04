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
        vector<string> fullJustify(vector<string> &words, int L) {
            //pack
            vector<vector<string>> groups;
            while (words.size()) {
                int len = 0;
                vector<string> g;
                while (words.size() && words.front().size() + len <= L) {
                    g.push_back(words.front());
                    len += words.front().size() + 1;
                    words.erase(words.begin());
                }
                if (g.size()) groups.push_back(g);
            }

            //adjust
            int j = 0;
            for (auto& x: groups) {
                string s = x.front();
                if (x.size() == 1) s += string(L - s.size(), ' ');
                else {
                    auto k = L;
                    for (auto& i: x) k -= i.size();
                    auto d = k / (x.size()-1), r = k % (x.size()-1);

                    if (j == groups.size()-1) {d = 0; r = x.size(); }
                    for (int i = 1; i < x.size(); i++) {
                        s += string((i <= r ? (d+1) : d), ' ') + x[i];
                        k -= d+(i<=r?1:0);
                    }
                    if (k) s += string(k, ' ');
                }
                words.push_back(s);
                j++;
            }

            return words;
        }
};

void test(const vector<string> &words, int L) {
    auto v = words;
    cout << Solution().fullJustify(v, L) << endl;
}

int main(int argc, char const *argv[])
{
    test({"This", "is", "an", "example", "of", "text", "justification."}, 16);
    test({"This", "a", "b"}, 5);
    test({"This", "a", "b"}, 10);
	return 0;
}
