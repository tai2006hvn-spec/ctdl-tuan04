#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int n = 5;
int cost_matrix[5][5] = {
    {0, 10, 9, 22, 23},
    {10, 0, 16, 19, 14},
    {9, 16, 0, 7, 28},
    {22, 19, 7, 0, 8},
    {23, 14, 28, 8, 0}
};

int best_cost = INT_MAX;
vector<int> best_route;
int nodes_count = 0;

int find_c_min() {
    int c_min = INT_MAX;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i != j && cost_matrix[i][j] < c_min)
                c_min = cost_matrix[i][j];
    return c_min;
}

void tsp(int curr_city, int count, int current_cost, vector<bool>& visited, vector<int>& route, bool use_bound, int c_min) {
    nodes_count++;
    
    if (count == n) {
        int total_cost = current_cost + cost_matrix[curr_city][0];
        if (total_cost < best_cost) {
            best_cost = total_cost;
            best_route = route;
            best_route.push_back(0);
        }
        return;
    }

    for (int next_city = 0; next_city < n; next_city++) {
        if (!visited[next_city] && cost_matrix[curr_city][next_city] > 0) {
            int new_cost = current_cost + cost_matrix[curr_city][next_city];
            
            if (use_bound) {
                int remaining_edges = n - count - 1;
                int lower_bound = new_cost + remaining_edges * c_min;
                if (lower_bound >= best_cost) continue;
            }
            
            visited[next_city] = true;
            route.push_back(next_city);
            tsp(next_city, count + 1, new_cost, visited, route, use_bound, c_min);
            route.pop_back();
            visited[next_city] = false;
        }
    }
}

int main() {
    int c_min = find_c_min();
    cout << "=== CHAY BAI TOAN NGUOI DU LICH (C++) ===" << endl;
    cout << "Canh re nhat toan ma tran c_min = " << c_min << endl;

    vector<bool> visited1(n, false);
    visited1[0] = true;
    vector<int> route1 = {0};
    nodes_count = 0;
    best_cost = INT_MAX;
    tsp(0, 1, 0, visited1, route1, true, c_min);
    int nodes_with_bound = nodes_count;
    int opt_cost = best_cost;
    vector<int> opt_route = best_route;

    vector<bool> visited2(n, false);
    visited2[0] = true;
    vector<int> route2 = {0};
    nodes_count = 0;
    best_cost = INT_MAX;
    tsp(0, 1, 0, visited2, route2, false, c_min);
    int nodes_without_bound = nodes_count;

    cout << "Chi phi hanh trinh toi uu       = " << opt_cost << endl;
    cout << "Hanh trinh toi uu               = ";
    for(size_t i = 0; i < opt_route.size(); ++i) {
        cout << opt_route[i] << (i == opt_route.size() - 1 ? "" : " -> ");
    }
    cout << endl;
    cout << "So nut khi Co cat nhanh         = " << nodes_with_bound << endl;
    cout << "So nut khi KHONG cat nhanh      = " << nodes_without_bound << endl;

    return 0;
}