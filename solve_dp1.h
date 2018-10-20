#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "utils.h"

vector<int> solve_dp1(int n,
                      int m,
                      const vector<int>& nObjectsInOrders,
                      const vector<int>& limits,
                      const vector<vector<int> >& orders);

vector<int> solve_dp1(int n,
                      int m,
                      const vector<int>& nObjectsInOrders,
                      const vector<int>& limits,
                      const vector<vector<int> >& orders) {
    vector<vector<int> > dp;
    vector<vector<int> > pre;
    vector<vector<vector<int> > > nObjectsInOrdersByStep;

    dp.resize(m + 1);
    pre.resize(m + 1);
    nObjectsInOrdersByStep.resize(m + 1);
    for(int i = 1; i <= m; ++i) {
        dp[i].resize(m);
        pre[i].resize(m);
        nObjectsInOrdersByStep[i].resize(m);
    }
    for(int i = 0; i < m; ++i) if (satisfy(orders[i], limits)) {
        dp[1][i] = sum(orders[i]);
        nObjectsInOrdersByStep[1][i] = orders[i];
    }

    for(int j = 1; j < m; ++j) {
        if (dp[1][j] > 0) {
            //cerr << "j = " << j << endl;
            for(int i = 2; i <= j + 1; ++i) {
                //cerr << "  i = " << i << endl;
                for(int k = 0; k < j; ++k) {
                    //cerr << "    k = " << k << endl;
                    if (dp[i-1][k] > 0) {
                        vector<int> newOrder = add(nObjectsInOrdersByStep[i-1][k], orders[j]);
                        if (satisfy(newOrder, limits)) {
                            //cerr << "      dp[" << i << "][" << j << "]" << " = " << dp[i][j] << "\n";
                            if (dp[i][j] < dp[i-1][k] + dp[1][j]) {
                                dp[i][j] = dp[i-1][k] + dp[1][j];
                                pre[i][j] = k;
                                nObjectsInOrdersByStep[i][j] = newOrder;
                            }
                            //cerr << "      dp[" << i << "][" << j << "]" << " = " << dp[i][j] << "\n";
                        }
                    }
                }
            }
        }
    }

    //print(dp);
    //print(pre);

    int res = m;
    bool found = false;
    while (res) {
        for(int i = res - 1; i < m; ++i) {
            if (dp[res][i] > 0) {
                found = true;
                break;
            }
        }
        if (found) break;
        --res;
    }

    //cerr << "res = " << res << endl;

    int maxItemsPos, maxItems, cur;
    set<int> ans;
    if (found) {
        maxItemsPos = res - 1;
        maxItems = dp[res][res - 1];
        for(int i = res; i < m; ++i) {
            if (dp[res][i] > maxItems) {
                maxItems = dp[res][i];
                maxItemsPos = i;
            }
        }

        ans.insert(maxItemsPos);
        cur = maxItemsPos;
        for(int i = res; i >= 2; --i) {
            ans.insert(pre[i][cur]);
            cur = pre[i][cur];
        }
    }

    vector<int> result;
    for(auto it = ans.begin(); it != ans.end(); ++it)
        result.push_back(*it);
    return result;
}

