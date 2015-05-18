#include <iostream>
#include <unordered_map>
#include <cassert>
#include <climits>
#include <vector>
#include <stack>
#include <cmath>
#include <cstring>
#include <random>
#include <map>
#include <algorithm>

using namespace std;

template<class T, class U>
ostream& operator<<(ostream& os, const unordered_map<T, U>& v)
{
    os << "{";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << "(" << x.first << ":" << x.second->val <<")";
    }
    return os << "}";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    bool first = true;
    for (const auto& x: v) {
        if (first) {
            first = false;
        } else 
            os << ",";
        os << x;
    }
    return os << "]";
}

//WTF.... still MLE..
class MinStack2 {
    public:
        void push(int x) {
            int m = mins.size() ? sp[mins.back()] : INT_MAX;
            sp.push_back(x);
            if (x < m) mins.push_back(sp.size()-1);
        }

        void pop() {
            if (sp.size()) {
                if (mins.back() == sp.size()-1) {
                    mins.pop_back();
                }
                sp.pop_back();
            }
        }

        int top() {
            return sp.back();
        }

        int getMin() {
            if (mins.size()) return sp[mins.back()];
            else return INT_MAX;
        }
        
        vector<int> sp;
        vector<int> mins;
};

// Fuck! MLE
class MinStack3 {
    public:
        void push(int x) {
            if (!sp.size()) {
                min = x;
                sp.push_back(0);
            } else {
                sp.push_back(x-min);
                if (min > x) min = x;
            }
        }

        void pop() {
            if (sp.size()) {
                auto x = sp.back();
                sp.pop_back();
                if (x < 0) min = min - x;
            }
        }

        int top() {
            if (sp.size()) {
                auto x = sp.back();
                if (x < 0) min = min - x;
                return x;
            }
            else return INT_MAX;
        }

        int getMin() {
            if (sp.size()) return min;
            return INT_MAX;
        }
        
        vector<int> sp;
        int min;
};

class MinStack {
    public:
        void push(int x) {
            if (!sp.size()) {
                min = x;
                sp.push(0);
            } else {
                sp.push(x-min);
                if (min > x) min = x;
            }
        }

        void pop() {
            if (sp.size()) {
                auto x = sp.top();
                sp.pop();
                if (x < 0) min = min - x;
            }
        }

        int top() {
            if (sp.size()) {
                long x = sp.top();
                if (x <= 0) { x = min; }
                else x = x+min;
                return x;
            }
            else return INT_MAX;
        }

        int getMin() { return min; }
        
        stack<long> sp;
        long min;
};

void test()
{
    MinStack ms;
    //ms.push(-1);
    //cout << "min: " << ms.getMin() << endl;
    //cout << "top: " << ms.top() << endl;

    ms.push(5);
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.push(4);
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.push(6);
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.push(1);
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.push(2);
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.push(3);
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;

    ms.pop();
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.pop();
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.pop();
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.pop();
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.pop();
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;
    ms.pop();
    cout << "min: " << ms.getMin() << endl;
    cout << "top: " << ms.top() << endl;

    ms.push(4);
    ms.push(1);
    ms.push(2);
    ms.push(1);
    ms.push(2);

    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
