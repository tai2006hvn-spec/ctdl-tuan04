class Item:
    def __init__(self, name, weight, value):
        self.name = name
        self.weight = weight
        self.value = value
        self.ratio = value / weight

def solve_knapsack(items, W, enable_pruning=True):
    items.sort(key=lambda x: x.ratio, reverse=True)
    n = len(items)
    best_val = 0
    best_comb = []
    node_count = [0]
    
    def bound(i, weight, value):
        b = value
        total_w = weight
        j = i
        while j < n and total_w + items[j].weight <= W:
            total_w += items[j].weight
            b += items[j].value
            j += 1
        if j < n:
            b += (W - total_w) * items[j].ratio
        return b

    def backtrack(i, current_w, current_v, current_items):
        node_count[0] += 1
        nonlocal best_val, best_comb
        
        if current_w <= W and current_v > best_val:
            best_val = current_v
            best_comb = list(current_items)
            
        if i == n:
            return
            
        if enable_pruning:
            if bound(i, current_w, current_v) <= best_val:
                return
                
        if current_w + items[i].weight <= W:
            current_items.append(items[i].name)
            backtrack(i + 1, current_w + items[i].weight, current_v + items[i].value, current_items)
            current_items.pop()
            
        backtrack(i + 1, current_w, current_v, current_items)

    backtrack(0, 0, 0, [])
    return best_val, best_comb, node_count[0]

if __name__ == "__main__":
    raw_items = [
        Item("A", 4, 19), Item("B", 7, 25), Item("C", 3, 7),
        Item("D", 3, 8), Item("E", 3, 9), Item("F", 10, 21)
    ]
    W = 14
    val_co, comb_co, nodes_co = solve_knapsack(list(raw_items), W, True)
    val_khong, comb_khong, nodes_khong = solve_knapsack(list(raw_items), W, False)
    
    print(f"Gia tri lon nhat: {val_co}, Tap chon: {comb_co}")
    print(f"So nut khi CO cat nhanh: {nodes_co}")
    print(f"So nut khi KHONG cat nhanh: {nodes_khong}")
    print(f"So nut giam duoc: {nodes_khong / nodes_co:.2f} lan")