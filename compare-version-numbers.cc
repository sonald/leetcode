#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cassert>

using namespace std;
#define VERSION  1

ostream& operator<<(ostream& os, const vector<int>& v)
{
    os << "[";
    for (auto i : v) {
        os << i << " ";
    }
    return os << "]";
}

#if VERSION == 1
class Solution {
    public:
        int compareVersion(string version1, string version2) {
            vector<int> v1 = split(version1), v2 = split(version2);
            cout << v1 << endl;
            cout << v2 << endl;

            for (int i = 0, len = std::min(v1.size(), v2.size()); i < len; i++) {
                if (v1[i] > v2[i]) return 1;
                else if (v1[i] < v2[i]) return -1;
            }

            if (v1.size() > v2.size()) {
                for (int i = v2.size(); i < v1.size(); i++) 
                    if (v1[i]) return 1;

            } else if (v1.size() < v2.size()) {
                for (int i = v1.size(); i < v2.size(); i++) 
                    if (v2[i]) return -1;
            }

            return 0;
        }

        vector<int> split(string ver) {
            vector<int> v;
            size_t start = 0;
            auto sz = ver.find('.', start);
            while (sz != string::npos) {
                auto s = ver.substr(start, sz-start);
                v.emplace_back(std::stoi(s));
                start = sz+1;
                sz = ver.find('.', start);
            }

            if (start < ver.size()) {
                auto s = ver.substr(start, ver.size()-start);
                v.emplace_back(std::stoi(s));
            }
            return v;
        }
};

#endif

int main(int argc, char *argv[])
{
    cout << Solution().compareVersion("1.2", "2.1") << endl;
    cout << Solution().compareVersion("1.2.0", "1.2") << endl; // 0
    cout << Solution().compareVersion("1.2.13", "1.2.5") << endl;
    cout << Solution().compareVersion("1.2.0.5", "1.2") << endl;
    return 0;
}
