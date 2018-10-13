#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "utils.h"

#define bits(n, i) ((n >> i) & 1)

vector<int> solve_greedy(int n,
                         int m,
                         const vector<int>& nObjectsInOrders,
                         const vector<int>& limits,
                         const vector<vector<int> >& orders);

int find_best_order(set<int>& satisfiedSet,
                    const vector<int>& limits,
                    const vector<vector<int> >& orders) {

}

int find_maximum_order_greedy(int n,
                              int m,
                              const vector<int>& nObjectsInOrders,
                              const vector<int>& limits,
                              const vector<vector<int> >& orders,
                              const vector<int>& n_items_per_order,
                              const vector<int>& satisfied_set) {
    if (satisfied_set.size() == 0) return 0;
    priority_queue<pair<int, int> > pq;
    for(int i : satisfied_set) pq.push(make_pair(-n_items_per_order[i], i));
    int len = 0;
    vector<int> join_order(n);
    while (true) {
        if (pq.size() == 0) break;
        pair<int, int> top = pq.top();
        pq.pop();
        int chosen_order = top.second;
        join_order = add(join_order, orders[chosen_order]);
        if (!satisfy(join_order, limits)) return len;
        else {
            ++len;
        }
    }
    return len;
}

void dfs(int n,
         const vector<int>& satisfied_set,
         const vector<int>& limits,
         const vector<vector<int> >& orders,
         int k, int depth, int max_len,
         vector<int>& cur_order,
         int& best_sum,
         vector<int>& best_order) {
    if (depth == max_len) {
        vector<int> join_order(n);
        for(int i : cur_order) join_order = add(join_order, orders[i]);
        if (satisfy(join_order, limits)) {
            int cur_sum = sum(join_order);
            if (cur_sum > best_sum) {
                best_sum = cur_sum;
                best_order = cur_order;
            }
        }
    }
    else {
        for(int i = k; i < satisfied_set.size() + depth - max_len + 1; ++i) {
            cur_order[depth] = satisfied_set[i];
            dfs(n, satisfied_set, limits, orders, i + 1, depth + 1,
                max_len, cur_order, best_sum, best_order);
        }
    }
}

vector<int> solve_greedy(int n,
                         int m,
                         const vector<int>& nObjectsInOrders,
                         const vector<int>& limits,
                         const vector<vector<int> >& orders) {
    vector<int> n_items_per_order(m);
    vector<bool> is_satisfied(m);
    vector<int> satisfied_set;
    for(int i = 0; i < m; ++i) {
        if (satisfy(orders[i], limits)) {
            is_satisfied[i] = true;
            n_items_per_order[i] = sum(orders[i]);
            satisfied_set.push_back(i);
        }
    }

    int max_len = find_maximum_order_greedy(n, m, nObjectsInOrders, limits, orders,
                                            n_items_per_order, satisfied_set);

    vector<int> best_order, cur_order(max_len);
    int best_sum = -1;
    dfs(n, satisfied_set, limits, orders, 0, 0, max_len, cur_order, best_sum, best_order);
    return best_order;
}
