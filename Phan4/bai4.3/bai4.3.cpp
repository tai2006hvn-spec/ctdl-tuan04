#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

long long count_seq = 0;
long long count_mrv = 0;

bool isValid(const vector<vector<int>>& b, int r, int c, int val) {
    for (int i = 0; i < 9; i++) {
        if (b[r][i] == val || b[i][c] == val) return false;
    }
    int start_r = (r / 3) * 3, start_c = (c / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[start_r + i][start_c + j] == val) return false;
        }
    }
    return true;
}

bool solveSeq(vector<vector<int>>& b) {
    count_seq++;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (b[r][c] == 0) {
                for (int val = 1; val <= 9; val++) {
                    if (isValid(b, r, c, val)) {
                        b[r][c] = val;
                        if (solveSeq(b)) return true;
                        b[r][c] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool solveMRV(vector<vector<int>>& b) {
    count_mrv++;
    int min_cand = 10;
    int best_r = -1, best_c = -1;
    
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (b[r][c] == 0) {
                int cand = 0;
                for (int val = 1; val <= 9; val++) {
                    if (isValid(b, r, c, val)) cand++;
                }
                if (cand < min_cand) {
                    min_cand = cand;
                    best_r = r;
                    best_c = c;
                }
            }
        }
    }
    
    if (best_r == -1) return true;
    
    for (int val = 1; val <= 9; val++) {
        if (isValid(b, best_r, best_c, val)) {
            b[best_r][best_c] = val;
            if (solveMRV(b)) return true;
            b[best_r][best_c] = 0;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> board = {
        {0, 0, 0, 0, 0, 6, 0, 0, 0},
        {0, 0, 8, 1, 0, 5, 0, 4, 0},
        {0, 0, 0, 9, 0, 0, 7, 0, 5},
        {0, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 1, 0, 0},
        {0, 7, 4, 0, 0, 0, 0, 2, 1},
        {0, 0, 0, 0, 1, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 9, 0, 0},
        {0, 9, 0, 0, 0, 0, 8, 0, 6}
    };

    vector<vector<int>> b1 = board;
    vector<vector<int>> b2 = board;

    auto start = chrono::high_resolution_clock::now();
    solveSeq(b1);
    auto end = chrono::high_resolution_clock::now();
    double time_seq = chrono::duration<double>(end - start).count();

    start = chrono::high_resolution_clock::now();
    solveMRV(b2);
    end = chrono::high_resolution_clock::now();
    double time_mrv = chrono::duration<double>(end - start).count();

    bool is_same = (b1 == b2);

    cout << "=== KET QUA BAI 4.3 (C++) ===" << endl;
    cout << "So loi goi (Quet tuan tu): " << count_seq << " | (MRV): " << count_mrv << endl;
    cout << "Thoi gian (Quet tuan tu): " << time_seq << "s | (MRV): " << time_mrv << "s" << endl;
    cout << "Loi giai tim duoc co giong nhau khong? " << (is_same ? "Co" : "Khong") << endl;

    return 0;
}