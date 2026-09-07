#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
    double ratio;
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

void backtrack(int i, int current_w, int current_v, int W, 
               const vector<Item>& items, int& best_val, 
               vector<string>& best_comb, vector<string>& current_comb, 
               long long& node_count, bool enable_pruning) {
    node_count++;
    int n = items.size();

    if (current_w <= W && current_v > best_val) {
        best_val = current_v;
        best_comb = current_comb;
    }

    if (i == n) return;

    if (enable_pruning) {
        double b = current_v;
        int total_w = current_w;
        int j = i;
        while (j < n && total_w + items[j].weight <= W) {
            total_w += items[j].weight;
            b += items[j].value;
            j++;
        }
        if (j < n) {
            b += (W - total_w) * items[j].ratio;
        }
        if (b <= best_val) return;
    }

    if (current_w + items[i].weight <= W) {
        current_comb.push_back(items[i].name);
        backtrack(i + 1, current_w + items[i].weight, current_v + items[i].value, 
                  W, items, best_val, best_comb, current_comb, node_count, enable_pruning);
        current_comb.pop_back();
    }

    backtrack(i + 1, current_w, current_v, W, items, best_val, best_comb, current_comb, node_count, enable_pruning);
}

int main() {
    vector<Item> raw_items = {
        {"A", 4, 19, 19.0/4}, {"B", 7, 25, 25.0/7}, {"C", 3, 7, 7.0/3},
        {"D", 3, 8, 8.0/3}, {"E", 3, 9, 9.0/3}, {"F", 10, 21, 21.0/10}
    };
    int W = 14;
    vector<Item> items_co = raw_items;
    vector<Item> items_khong = raw_items;
    sort(items_co.begin(), items_co.end(), compareItems);
    sort(items_khong.begin(), items_khong.end(), compareItems);

    int best_val_co = 0; long long nodes_co = 0;
    vector<string> best_comb_co, curr_co;
    backtrack(0, 0, 0, W, items_co, best_val_co, best_comb_co, curr_co, nodes_co, true);

    int best_val_khong = 0; long long nodes_khong = 0;
    vector<string> best_comb_khong, curr_khong;
    backtrack(0, 0, 0, W, items_khong, best_val_khong, best_comb_khong, curr_khong, nodes_khong, false);

    cout << "So nut khi CO cat nhanh: " << nodes_co << endl;
    cout << "So nut khi KHONG cat nhanh: " << nodes_khong << endl;
    cout << "So nut giam duoc: " << (double)nodes_khong / nodes_co << " lan" << endl;
    return 0;
}