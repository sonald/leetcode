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

class Solution {
    bool loop {false};
    bool visited[10000];
    unordered_set<int> sp;

public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> adjs(numCourses, vector<int>());

        for (auto& p: prerequisites) {
            adjs[p.first].push_back(p.second);
        }
        return !hasLoop(adjs);
    }

    bool hasLoop(vector<vector<int>>& adjs) {
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < adjs.size(); i++) {
            if (loop) break;
            if (!visited[i]) {
                visited[i] = true;
                sp.insert(i);
                dfs(adjs, i);
                sp.erase(i);
            }
        }

        return loop;
    }

    void dfs(vector<vector<int>>& adjs, int u) {
        for (auto v: adjs[u]) {
            if (loop) break;

            if (!visited[v]) {
                visited[v] = true;
                sp.insert(v);
                dfs(adjs, v);
                sp.erase(v);
            } else {
                if (sp.find(v) != sp.end()) {
                    loop = true; break;
                }
            }
        }
    }
};

int main(int argc, char *argv[])
{
    {
        vector<pair<int, int>> edges = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};
        cout << Solution().canFinish(4, edges) << endl; //0
    }
    {
        vector<pair<int, int>> edges = {{1,0},{2,6},{1,7},{6,4},{7,0},{0,5}};
        cout << Solution().canFinish(8, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {{1, 0}, {0, 1}};
        cout << Solution().canFinish(2, edges) << endl; // 0
    }
    {
        vector<pair<int, int>> edges = {{1, 0}, {2, 0}};
        cout << Solution().canFinish(3, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 2}};
        cout << Solution().canFinish(3, edges) << endl; //1
    }
    {
        vector<pair<int, int>> edges = {{1, 0}};
        cout << Solution().canFinish(2, edges) << endl; //1
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
        cout << Solution().canFinish(5, edges) << endl; //0
    }
    return 0;
}
