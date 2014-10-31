#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, vector<vector<int>> vvi)
{
    for (const auto& vi: vvi) {
        os << "<";
        for (auto i: vi) {
            os << i << ",";
        }
        os << ">" << endl;
    }

    return os;
}
class Solution2 {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(),num.end());
        
        vector<vector<int> > r;
        vector<int> a;
        int len = num.size();
 
        if( len < 3 || num[0] > 0 || num[len-1] < 0 )
        {
            return r;
        }
 
        int i,j,k,sum,tempj,tempk,prev=num[0]-1;
 
        for( i = 0; i < len-2 && num[i] < 0; ++i )//outer for
        {
            if( num[i] == prev )
            {
                continue;
            }
            prev = num[i];
            for( j = i+1, k = len-1; j < k ;)//inner for
            {
                sum = num[i] + num[j] + num[k];
                if( sum == 0 )
                {
                    a.push_back(num[i]);
                    a.push_back(num[j]);
                    a.push_back(num[k]);
                    r.push_back(a);
                    a.clear();
                    tempj = num[j];
                    tempk = num[k];
                    while( j < k && num[j] == tempj )
                        ++j;
                    while( k > j && num[k] == tempk )
                        --k;
                }
                else if( sum < 0 )
                {
                    tempj = num[j];
                    while( j < k && num[j] == tempj )
                        ++j;
                }
                else
                {
                    tempk = num[k];
                    while( k > j && num[k] == tempk )
                        --k;
                }
            }//end inner for
        }//end outer for
 
        if( i < len-2 && num[i] == 0 && num[i+1] == 0 && num[i+2] == 0 )
        {
            a.assign(3,0);
            r.push_back(a);
        }
        return r;
    }
};

// memory limit exceeded
class Solution {
    public:
        vector<vector<int> > threeSum(vector<int> &num) {
            vector<vector<int>> vvi;
            auto len = num.size();

            if (len < 3) return vvi;
            std::sort(num.begin(), num.end());

            int i = 0, j = 1, k = 2;
            while (i < len-2 && num[i] <= 0) {
                if (num[i] + num[j] + num[k] == 0) {
                    vvi.push_back({num[i], num[j], num[k]});
                }

                while (k < len && (num[k] == num[k+1])) k++;
                k++;
                if (k == len) {
                    while (j+2 < len && num[j] == num[j+1]) j++;
                    j++; k = j+1;
                }
                if (j+1 >= len) {
                    while (i+3 < len && num[i] == num[i+1]) i++;
                    i++; j = i+1; k = j+1;
                }
            }


            return vvi;
        }
};

bool compr(const vector<vector<int>>& vv1, const vector<vector<int>>& vv2)
{
    if (vv1.size() != vv2.size()) return false;

    for (int i = 0; i < vv1.size(); ++i) {
        auto v1 = vv1[i], v2 = vv2[i];
        if (v1[0] != v2[0]) return false;
        if (v1[1] != v2[1]) return false;
        if (v1[2] != v2[2]) return false;
    }

    return true;
}

void test(const vector<int>& vs)
{
    Solution sol;
    Solution2 sol2;
    vector<int> vs2 {vs};
    cout << sol.threeSum(vs2) << compr(sol.threeSum(vs2), sol2.threeSum(vs2)) << endl;

}

int main(int argc, char *argv[])
{
    test({-1, 0, 1, 2, -1, -4});
    test({-1, 0, 1});
    test({0, 0, 0, 0, 0});
    test({-2, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2});
    test({-1, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2});

    vector<int> vs(300);
    std::default_random_engine dre;
    std::uniform_int_distribution<> di{-10000, 10000};
    for (auto& i: vs) {
        i = di(dre);
    }
    test(vs);

    return 0;
}

