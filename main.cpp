#include <bits/stdc++.h>
using namespace std;

#include "utils.h"
#include "brute_force.h"
#include "solve_dp1.h"
#include "solve_greedy.h"

const int MAXN = 100;
const int MAXM = 15;

double total_loss_dp1 = 0.0;
double total_loss_greedy = 0.0;
double total_best_loss = 0.0;

int n_tests_solved_dp1 = 0;
int n_tests_solved_greedy = 0;

int n_tests_passed_by_dp1 = 0;
int n_tests_passed_by_greedy = 0;

string input_prefix = "test/in";
//string input_prefix = "in";

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

pair<vector<string>, double> solve(string input, auto& fout) {
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
    vector<int> result_dp1 = solve_dp1(n, m, nObjectsInOrders, limits, orders);
    vector<int> result_greedy = solve_greedy(n, m, nObjectsInOrders, limits, orders);

    // Print out result of each method
    fout << "Bruteforce:\n";
    print_result(result_bruteforce, orderId, fout);
    fout << "DP1:\n";
    print_result(result_dp1, orderId, fout);
    fout << "Greedy:\n";
    print_result(result_greedy, orderId, fout);
    fout << '\n';

    // Evaluate result of each method
    vector<int> order_groundtruth = total_order(result_bruteforce, n, orders);
    double loss_dp_1 = evaluate(result_dp1, result_bruteforce, order_groundtruth, n, orders);
    double loss_greedy = evaluate(result_greedy, result_bruteforce, order_groundtruth, n, orders);
    fout << "loss_dp1: " << loss_dp_1 << '\n';
    fout << "loss_greedy: " << loss_greedy << '\n';
    fout << '\n';

    // Update global loss
    total_loss_dp1 += loss_dp_1;
    total_loss_greedy += loss_greedy;

    // Find minimum loss and return result of minimum loss method
    vector<double> loss = {loss_dp_1, loss_greedy};
    double min_loss = *min_element(loss.begin(), loss.end());

    pair<vector<string>, double> ans;
    if (equal(min_loss, loss_dp_1)) {
        ++n_tests_solved_dp1;
        ans = make_pair(get_result(result_dp1, orderId), loss_dp_1);
    }
    if (equal(min_loss, loss_greedy)) {
        ++n_tests_solved_greedy;
        ans = make_pair(get_result(result_greedy, orderId), loss_greedy);
    }

    if (equal(loss_dp_1, 0.0)) ++n_tests_passed_by_dp1;
    if (equal(loss_greedy, 0.0)) ++n_tests_passed_by_greedy;

    return ans;
}

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
    vector<int> result_dp1 = solve_dp1(n, m, nObjectsInOrders, limits, orders);
    vector<int> result_greedy = solve_greedy(n, m, nObjectsInOrders, limits, orders);

    // Print out result of each method
    fout << "DP1:\n";
    print_result(result_dp1, orderId, fout);
    fout << "Greedy:\n";
    print_result(result_greedy, orderId, fout);
    fout << '\n';

    // Choose the best result
    pair<vector<string>, string> ans;
    int comp = compare_solution(result_dp1, result_greedy, n, orders);
    switch (comp) {
        case -1: {
            ++n_tests_solved_greedy;
            ans = make_pair(get_result(result_greedy, orderId), "Greedy");
            break;
        }
        case 1: {
            ++n_tests_solved_dp1;
            ans = make_pair(get_result(result_dp1, orderId), "DP1");
            break;
        }
        default: {
            ++n_tests_solved_greedy;
            ++n_tests_solved_dp1;
            ans = make_pair(get_result(result_greedy, orderId), "DP1-Greedy");
        }
    }
    return ans;
}

void test_1() {
    string output = "result/output1";
    std::fstream fout (output.c_str(), std::ios_base::out);
    int n_test = 360;
    int n_test_pass = 0;
    for(int i = 0; i < n_test; ++i) {
        string input = input_prefix + to_string(i);
        pair<vector<string>, double> res = solve(input, fout);
        vector<string> best_approximation = res.first;
        double loss = res.second;
        total_best_loss += loss;
        if (equal(loss, 0.0)) ++n_test_pass;
        fout << "Best approximation --- loss = " << loss << '\n';
        print(best_approximation, fout);
        fout << "\n---------------------------------------------------\n";
    }

    fout << "Evaluation\n";
    fout << "mean_loss_dp_1: " << total_loss_dp1/n_test << '\n';
    fout << "mean_loss_greedy: " << total_loss_greedy/n_test << '\n';
    fout << '\n';
    fout << "mean_best_loss: " << total_best_loss/n_test << '\n';
    fout << "N passed tests: " << n_test_pass << '\n';
    fout << "Percent of passed tests: " << 100.0*n_test_pass/n_test << '\n';

    fout << '\n';
    fout << "N tests passed by dp1: " << n_tests_passed_by_dp1 << " " << 100.0*n_tests_passed_by_dp1/n_test << '\n';
    fout << "N tests passed by greedy: " << n_tests_passed_by_greedy << " " << 100.0*n_tests_passed_by_greedy/n_test << '\n';

    fout << '\n';
    fout << "N tests solved by dp1: " << n_tests_solved_dp1 << " " << 100.0*n_tests_solved_dp1/n_test << '\n';
    fout << "N tests solved by greedy: " << n_tests_solved_greedy << " " << 100.0*n_tests_solved_greedy/n_test << '\n';

    fout.close();
}

void test_2() {
    string output = "result/output2";
    std::fstream fout (output.c_str(), std::ios_base::out);
    int n_test = 360;
    int n_test_pass = 0;
    for(int i = 0; i < n_test; ++i) {
        string input = input_prefix + to_string(i);
        pair<vector<string>, string> res = solve_without_bruteforce(input, fout);
        string method = res.second;
        vector<string> ans = res.first;
        fout << "Best approximation: " << method << '\n';
        print(ans, fout);
        fout << "\n---------------------------------------------------\n";
    }

    fout << "Evaluation\n";
    fout << "N tests solved by dp1: " << n_tests_solved_dp1 << " " << 100.0*n_tests_solved_dp1/n_test << '\n';
    fout << "N tests solved by greedy: " << n_tests_solved_greedy << " " << 100.0*n_tests_solved_greedy/n_test << '\n';
    int n_tests_solved_by_both = n_tests_solved_dp1 + n_tests_solved_greedy - n_test;
    fout << "N tests solved by both: " << n_tests_solved_by_both << " " << 100.0*n_tests_solved_by_both/n_test << '\n';

    fout.close();
}

int main() {
    test_1();
    test_2();
    return 0;
}
