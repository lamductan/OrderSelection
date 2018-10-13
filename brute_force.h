#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "utils.h"

#define bits(n, i) ((n >> i) & 1)

vector<int> solve_bruteforce(int n,
                             int m,
                             const vector<int>& nObjectsInOrders,
                             const vector<int>& limits,
                             const vector<vector<int> >& orders);


vector<int> solve_bruteforce(int n,
                             int m,
                             const vector<int>& nObjectsInOrders,
                             const vector<int>& limits,
                             const vector<vector<int> >& orders) {
    int best_length = -1, best_n_items = -1;
    int best_result;
    for(long long i = 1LL; i < (1LL << m); ++i) {
        vector<int> new_order(n);
        int n_orders = 0;
        for(int j = 0; j < m; ++j) {
            if (bits(i, j)) {
                new_order = add(new_order, orders[j]);
                ++n_orders;
            }
        }
        if (n_orders >= best_length) {
            if (satisfy(new_order, limits)) {
                int new_sum = sum(new_order);
                if (n_orders > best_length || new_sum > best_n_items) {
                    best_length = n_orders;
                    best_n_items = new_sum;
                    best_result = i;
                }
            }
        }
    }

    vector<int> ans;
    for(int i = 0; i < m; ++i) if (bits(best_result, i))
        ans.push_back(i);
    return ans;
}
