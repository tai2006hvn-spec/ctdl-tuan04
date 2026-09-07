import sys

cost_matrix = [
    [0, 10, 9, 22, 23],
    [10, 0, 16, 19, 14],
    [9, 16, 0, 7, 28],
    [22, 19, 7, 0, 8],
    [23, 14, 28, 8, 0]
]

n = 5

c_min = min(min(val for val in row if val > 0) for row in cost_matrix)

best_cost = sys.maxsize
best_route = []
nodes_count = 0

def tsp(curr_city, count, current_cost, visited, route, use_bound):
    global best_cost, best_route, nodes_count
    nodes_count += 1
    
    if count == n:
        total_cost = current_cost + cost_matrix[curr_city][0]
        if total_cost < best_cost:
            best_cost = total_cost
            best_route = route + [0]
        return

    for next_city in range(n):
        if not visited[next_city] and cost_matrix[curr_city][next_city] > 0:
            new_cost = current_cost + cost_matrix[curr_city][next_city]
            
            if use_bound:
                remaining_edges = n - count - 1
                lower_bound = new_cost + remaining_edges * c_min
                if lower_bound >= best_cost:
                    continue
            
            visited[next_city] = True
            tsp(next_city, count + 1, new_cost, visited, route + [next_city], use_bound)
            visited[next_city] = False

print("=== CHẠY BÀI TOÁN NGƯỜI DU LỊCH (PYTHON) ===")
print(f"Cạnh rẻ nhất toàn ma trận c_min = {c_min}")

# 1. Chạy CÓ cắt nhánh
visited = [False] * n
visited[0] = True
nodes_count = 0
best_cost = sys.maxsize
best_route = []
tsp(0, 1, 0, visited, [0], True)
nodes_with_bound = nodes_count
optimal_cost = best_cost
optimal_route = best_route

visited = [False] * n
visited[0] = True
nodes_count = 0
best_cost = sys.maxsize
tsp(0, 1, 0, visited, [0], False)
nodes_without_bound = nodes_count

print(f"Chi phí hành trình tối ưu       = {optimal_cost}")
print(f"Hành trình tối ưu               = {' -> '.join(map(str, optimal_route))}")
print(f"Số nút khi CÓ cắt nhánh         = {nodes_with_bound}")
print(f"Số nút khi KHÔNG cắt nhánh      = {nodes_without_bound}")