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
#include <cassert>

using namespace std;
ostream& operator<<(ostream& os, const vector<int>& v)
{
    os << "[";
    for (auto i: v) {
        os << i << ",";
    }
    return os << "]";
}

class Solution {
    bool loop {false};
    bool visited[10000];
    unordered_map<int, int> pp; //parent pointer
    unordered_set<int> sp;
    vector<int> res;

public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> adjs(numCourses, vector<int>());

        for (auto& p: prerequisites) {
            adjs[p.first].push_back(p.second);
        }

        help(adjs);
        if (loop) return {};
        return res;
    }

    void help(vector<vector<int>>& adjs) {
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < adjs.size(); i++) {
            if (loop) break;
            if (pp.find(i) == pp.end()) {
                pp[i] = -1;
                sp.insert(i);
                dfs(adjs, i);
                sp.erase(i);
            }
        }
    }

    void dfs(vector<vector<int>>& adjs, int u) {
        for (auto v: adjs[u]) {
            if (loop) break;

            if (pp.find(v) == pp.end()) {
                pp[v] = u;
                sp.insert(v);
                dfs(adjs, v);
                sp.erase(v);
            } else {
                if (sp.find(v) != sp.end()) {
                    loop = true; break;
                }
            }
        }

        res.push_back(u);
    }
};

int main(int argc, char *argv[])
{
    {
        vector<pair<int, int>> edges = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};
        cout << Solution().findOrder(4, edges) << endl; //0
    }
    {
        vector<pair<int, int>> edges = {{1,0},{2,6},{1,7},{6,4},{7,0},{0,5}};
        cout << Solution().findOrder(8, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {{1, 0}, {0, 1}};
        cout << Solution().findOrder(2, edges) << endl; // 0
    }
    {
        vector<pair<int, int>> edges = {{1, 0}, {2, 0}};
        cout << Solution().findOrder(3, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 2}};
        cout << Solution().findOrder(3, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {{1, 0}};
        cout << Solution().findOrder(2, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {
            {0, 1},
            {1, 2},
            {1, 3},
            {2, 1},
            {2, 4},
            {3, 4}
        };
        cout << Solution().findOrder(5, edges) << endl; //0
    }
    return 0;
}

