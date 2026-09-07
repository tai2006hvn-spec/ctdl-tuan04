#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int n;
vector<int> x;
vector<int> col, dcc, dcp;
long long node_count = 0;
int solution_count = 0;
vector<int> first_solution;

long long factorial(int num) {
    long long res = 1;
    for (int i = 1; i <= num; i++) {
        res *= i;
    }
    return res;
}

void print_grid_board(const vector<int>& sol) {
    int board_n = sol.size() - 1;
    cout << "\n--- HINH ANH BAN CO CHO n = " << board_n << " ---" << endl;
    string border = "+";
    for (int i = 0; i < board_n; i++) border += "---+";
    
    cout << border << endl;
    for (int i = 1; i <= board_n; i++) {
        string row_str = "|";
        for (int j = 1; j <= board_n; j++) {
            if (sol[i] == j) row_str += " Q |";
            else row_str += "   |";
        }
        cout << row_str << endl;
        cout << border << endl;
    }
}

void backtrack(int i) {
    node_count++;
    for (int j = 1; j <= n; j++) {
        if (col[j] == 0 && dcc[i - j + n] == 0 && dcp[i + j] == 0) {
            x[i] = j;
            col[j] = 1;
            dcc[i - j + n] = 1;
            dcp[i + j] = 1;
            
            if (i == n) {
                solution_count++;
                if (solution_count == 1) {
                    first_solution = x;
                }
            } else {
                backtrack(i + 1);
            }
            
            col[j] = 0;
            dcc[i - j + n] = 0;
            dcp[i + j] = 0;
        }
    }
}

int main() {
    cout << "Nhap kich thuoc n: ";
    cin >> n;
    x.resize(n + 1);
    col.assign(n + 1, 0);
    dcc.assign(2 * n + 1, 0);
    dcp.assign(2 * n + 1, 0);

    backtrack(1);

    long long fact_n = factorial(n);
    double ratio = (double)node_count / fact_n;

    cout << "Tong so nut da duyet: " << node_count << endl;
    cout << "Tong so loi giai tim duoc: " << solution_count << endl;
    cout << "So hoan vi neu vet can (n!): " << fact_n << endl;
    cout << "Ti le nut / n!: " << fixed << setprecision(4) << ratio << endl;

    if (solution_count > 0) {
        cout << "Loi giai dau tien (mang cot): ";
        for (int i = 1; i <= n; i++) {
            cout << first_solution[i] << " ";
        }
        cout << endl;
        print_grid_board(first_solution);
    }
    return 0;
}