#pragma once
#include <bits/stdc++.h>
#include "utils.h"
using namespace std;

struct solution {
    int len;
    int n_items;
    int method;
    solution(int len, int n_items, int method): len(len), n_items(n_items), method(method) {}
    bool operator < (solution other) const {
        return (len < other.len || (len == other.len && n_items < other.n_items));
    }
};

pair<vector<int>, int> choose_best_result(const vector<vector<int> >& results, int n, const vector<vector<int> >& orders) {
    vector<solution> solutions;
    int n_methods = results.size();
    for(int i = 0; i < n_methods; ++i) {
        vector<int> totalOrder = total_order(results[i], n, orders);
        int solution_len = results[i].size();
        int solution_n_items = sum(totalOrder);
        int solution_method = i;
        solutions.push_back(solution(solution_len, solution_n_items, solution_method));
    }

    sort(solutions.begin(), solutions.end());

    /*
    cerr << "Solutions after sorted:\n";
    for(auto sol : solutions) {
        cerr << sol.len << ' ' << sol.n_items << ' ' << sol.method << '\n';
    }
    cerr << '\n';
    */

    int best_method = solutions[n_methods - 1].method;
    vector<int> best_result = results[best_method];
    return make_pair(best_result, best_method);
}
