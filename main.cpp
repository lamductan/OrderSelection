#include <bits/stdc++.h>
using namespace std;

#include "utils.h"
#include "brute_force.h"
/* Add other methods here. Change above lines if you increase or decrease number of used methods */
#include "solve_dp1.h"
#include "solve_dp2.h"
#include "solve_greedy.h"
/* Add other methods here. Change above lines if you increase or decrease number of used methods */
#include "choose_best_result.h"

const int MAXN = 100;
const int MAXM = 15;

//double total_loss_dp1 = 0.0;
//double total_loss_greedy = 0.0;
//double total_best_loss = 0.0;

//int n_tests_solved_dp1 = 0;
//int n_tests_solved_greedy = 0;

//int n_tests_passed_by_dp1 = 0;
//int n_tests_passed_by_greedy = 0;

string input_prefix = "test/in";
//string input_prefix = "in";
int n_tests = 180; // Change if you change number of testcases

/* Add other methods here. Change below lines if you increase or decrease number of used methods */
int n_methods = 3; // Change if you increase or decrease number of used methods
string methods[] = {"DP1", "DP2", "Greedy"}; // Change if you increase or decrease number of used methods
int n_tests_passed_by_method[] = {0, 0, 0}; // Change if you increase or decrease number of used methods
/* Add other methods here. Change above lines if you increase or decrease number of used methods */

double total_loss = 0.0;
int n_tests_passed = 0;


void read(string input,
          int& n, int &m,
          map<string, int>& objectId,
          map<int, string>& orderId,
          vector<int>& nObjectsInOrders,
          vector<int>& limits,
          vector<vector<int> >& orders) {
    std::fstream fin (input.c_str(), std::ios_base::in);
    fin.tie(0);
    fin >> n;
    string s;
    int x;
    limits.resize(n);
    for(int i = 0; i < n; ++i) {
        fin >> s >> x;
        objectId[s] = i;
        limits[i] = x;
    }

    fin >> m;
    orders.resize(m);
    nObjectsInOrders.resize(m);
    string orderStr, objectStr;
    for(int i = 0 ; i < m; ++i) {
        fin >> nObjectsInOrders[i];
    }
    for(int i = 0; i < m; ++i) {
        orders[i].resize(n);
        for(int j = 0; j < nObjectsInOrders[i]; ++j) {
            fin >> orderStr >> objectStr >> x;
            orderId[i] = orderStr;
            orders[i][objectId[objectStr]] = x;
        }
    }
    fin.close();
    return;
}


/* Solve with bruteforce */
struct SolutionWithBruteforce {
    vector<string> list_orders;
    double loss;
    string method;
    SolutionWithBruteforce(const vector<string>& list_orders, double loss, string method):
        list_orders(list_orders), loss(loss), method(method) {}
};

SolutionWithBruteforce solve_with_bruteforce(string input, auto& fout) {
    // Parameters
    int n, m;
    map<string, int> objectId;
    map<int, string> orderId;
    vector<int> nObjectsInOrders;
    vector<int> limits;
    vector<vector<int> > orders;

    // Read input
    read(input, n, m, objectId, orderId, nObjectsInOrders, limits, orders);
    fout << input << '\n';

    // Solve problem by multiple methods
    vector<int> result_bruteforce = solve_bruteforce(n, m, nObjectsInOrders, limits, orders);
    vector<vector<int> > results;

    /* Add other methods here. Change below lines if you increase or decrease number of used methods */
    results.push_back(solve_dp1(n, m, nObjectsInOrders, limits, orders));
    results.push_back(solve_dp2(n, m, nObjectsInOrders, limits, orders));
    results.push_back(solve_greedy(n, m, nObjectsInOrders, limits, orders));
    /* Add other methods here. Change above lines if you increase or decrease number of used methods */

    // Print out result of each method
    fout << "Bruteforce:\n";
    print_result(result_bruteforce, orderId, fout);
    for(int i = 0; i < n_methods; ++i) {
        fout << "Method: " << methods[i] << '\n';
        print_result(results[i], orderId, fout);
    }
    fout << '\n';
    // Choose best method and evaluate with bruteforce
    pair<vector<int>, int> best_result = choose_best_result(results, n, orders);
    double loss = evaluate(best_result.first, result_bruteforce, n, orders);
    vector<string> list_orders = get_result(best_result.first, orderId);
    string method = methods[best_result.second];
    ++n_tests_passed_by_method[best_result.second];
    return SolutionWithBruteforce(list_orders, loss, method);
}

void test_with_bruteforce() {
    string output = "result/output_with_bruteforce";
    std::fstream fout (output.c_str(), std::ios_base::out);
    for(int i = 0; i < n_tests; ++i) {
        string input = input_prefix + to_string(i);
        SolutionWithBruteforce res = solve_with_bruteforce(input, fout);
        vector<string> best_approximation = res.list_orders;

        double loss = res.loss;
        string method = res.method;
        if (equal(loss, 0.0)) ++n_tests_passed;
        else total_loss += loss;

        fout << "Best approximation --- method = " << method << " --- loss = " << loss << '\n';
        print(best_approximation, fout);
        fout << "\n---------------------------------------------------\n";
    }

    fout << "Evaluation\n";
    fout << "N passed tests: " << n_tests_passed << '\n';
    fout << "Percent of passed tests: " << 100.0*n_tests_passed/n_tests << '\n';
    fout << "Mean loss: " << total_loss/n_tests << '\n';

    fout << '\n';
    for(int i = 0; i < n_methods; ++i) {
        fout << "N tests passed by " << methods[i] << ": " << n_tests_passed_by_method[i] << " " << 100.0*n_tests_passed_by_method[i]/n_tests << '\n';
    }

    fout.close();
}
/* Solve with bruteforce */


/* Solve without bruteforce */
pair<vector<string>, string> solve_without_bruteforce(string input, auto& fout) {
    // Parameters
    int n, m;
    map<string, int> objectId;
    map<int, string> orderId;
    vector<int> nObjectsInOrders;
    vector<int> limits;
    vector<vector<int> > orders;

    // Read input
    read(input, n, m, objectId, orderId, nObjectsInOrders, limits, orders);
    fout << input << '\n';

    // Solve problem by multiple methods
    vector<vector<int> > results;

    /* Add other methods here. Change below lines if you increase or decrease number of used methods */
    results.push_back(solve_dp1(n, m, nObjectsInOrders, limits, orders));
    results.push_back(solve_dp2(n, m, nObjectsInOrders, limits, orders));
    results.push_back(solve_greedy(n, m, nObjectsInOrders, limits, orders));
    /* Add other methods here. Change above lines if you increase or decrease number of used methods */

    // Print out result of each method
    for(int i = 0; i < n_methods; ++i) {
        fout << "Method: " << methods[i] << '\n';
        print_result(results[i], orderId, fout);
    }
    fout << '\n';

    // Choose the best result
    pair<vector<int>, int> best_result = choose_best_result(results, n, orders);
    return make_pair(get_result(best_result.first, orderId), methods[best_result.second]);
}

void test_without_bruteforce() {
    string output = "result/output_without_bruteforce";
    fstream fout (output.c_str(), ios_base::out);
    int n_test_pass = 0;
    for(int i = 0; i < n_tests; ++i) {
        string input = input_prefix + to_string(i);
        pair<vector<string>, string> res = solve_without_bruteforce(input, fout);
        string method = res.second;
        vector<string> ans = res.first;

        fout << "Best approximation: " << method << '\n';
        print(ans, fout);
        fout << "\n---------------------------------------------------\n";
    }
    fout.close();
}
/* Solve without bruteforce */

void test_single_method(string method) {
    string input = input_prefix + "3";
    // Parameters
    int n, m;
    map<string, int> objectId;
    map<int, string> orderId;
    vector<int> nObjectsInOrders;
    vector<int> limits;
    vector<vector<int> > orders;
    read(input, n, m, objectId, orderId, nObjectsInOrders, limits, orders);

    vector<int> result;
    if (method == "DP2")
        result = solve_dp2(n, m, nObjectsInOrders, limits, orders);
    else if (method == "DP1")
        result = solve_dp1(n, m, nObjectsInOrders, limits, orders);
    else if (method == "Greedy")
        result = solve_greedy(n, m, nObjectsInOrders, limits, orders);
    else result = solve_bruteforce(n, m, nObjectsInOrders, limits, orders);
    vector<string> ans = get_result(result, orderId);
    for(string x : ans) cout << x << ' ';
    cout << '\n';
}


int main() {
    test_with_bruteforce();
    test_without_bruteforce();
    //test_single_method("DP2");
    //cerr << '\n';
    //test_single_method("DP1");
    //cerr << '\n';
    return 0;
}
