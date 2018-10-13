#pragma once
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

bool satisfy(const vector<int>& order, const vector<int> &limits) {
    int n = order.size();
    for(int i = 0; i < n; ++i) {
        if (order[i] > limits[i]) return false;
    }
    return true;
}

int sum(const vector<int>& a) {
    int s = 0;
    for(int x : a) s += x;
    return s;
}

vector<int> add(const vector<int> &a, const vector<int>& b) {
    int sz = a.size();
    vector<int> res(sz);
    for(int i = 0; i < sz; ++i)
        res[i] = a[i] + b[i];
    return res;
}

vector<int> sub(const vector<int> &a, const vector<int>& b) {
    int sz = a.size();
    vector<int> res(sz);
    for(int i = 0; i < sz; ++i)
        res[i] = a[i] - b[i];
    return res;
}

void print(const vector<int>& a) {
    for(int x : a) cerr << x << " ";
    cerr << '\n';
}

void print(const vector<vector<int> >& a) {
    cerr << a.size() << endl;
    for(auto v: a) {
        for(int x: v) cerr << x << " ";
        cerr << endl;
    }
    cerr << endl;
}

void print(const vector<string>& a, auto& fout=cout) {
//    if (fout == NULL) {
//        for(string s: a) cout << s << " ";
//        cout << '\n';
//    }
//    else {
        for(string s: a) fout << s << " ";
        fout << '\n';
//    }
}

vector<int> total_order(const vector<int>& result, int n, const vector<vector<int> >& orders) {
    vector<int> total(n);
    for(int i: result) total = add(total, orders[i]);
    return total;
}

double evaluate(const vector<int>& result,
                const vector<int>& groundtruth,
                const vector<int>& order_groundtruth,
                int n,
                const vector<vector<int> >& orders) {
    int len_result = result.size();
    int len_groundtruth = groundtruth.size();
    if (len_groundtruth > len_result)
        return 1.0*(len_groundtruth - len_result);
    else {
        vector<int> order_result = total_order(result, n, orders);
        int n_item_result = sum(order_result);
        int n_item_groundtruth = sum(order_groundtruth);
        return 1.0 - 1.0*n_item_result / n_item_groundtruth;
    }
}

vector<string> get_result(const vector<int>& result, map<int, string>& orderId) {
    vector<string> res;
    for(int id: result) {
        res.push_back(orderId[id]);
    }
    return res;
}

void print_result(const vector<int>& result, map<int, string>& orderId, auto& fout=cout) {
//    if (fout == NULL) {
//        for(int id: result) {
//            cout << orderId[id] << " ";
//        }
//        cout << endl;
//    } else {
        for(int id: result) {
            fout << orderId[id] << " ";
        }
        fout << endl;
//    }
}

bool check(const vector<int>& result, const vector<int>& limits, const vector<vector<int> >& orders) {
    vector<int> total_order;
    for(int i : result) total_order = add(total_order, orders[i]);
    return satisfy(total_order, limits);
}

bool equal(double a, double b) {
    return fabs(a - b) < eps;
}

int compare_solution(const vector<int>& result1, const vector<int>& result2, int n, const vector<vector<int> >& orders) {
    if (result1.size() > result2.size()) return 1;
    if (result1.size() < result2.size()) return -1;

    vector<int> total_order_1 = total_order(result1, n, orders);
    vector<int> total_order_2 = total_order(result2, n, orders);
    int sum1 = sum(total_order_1);
    int sum2 = sum(total_order_2);
    if (sum1 > sum2) return 1;
    if(sum1 < sum2) return -1;
    return 0;
}
