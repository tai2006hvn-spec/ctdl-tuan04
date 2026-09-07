const cost_matrix = [
    0  10   9  22  23;
   10   0  16  19  14;
    9  16   0   7  28;
   22  19   7   0   8;
   23  14  28   8   0
]

const n = 5

c_min = minimum([cost_matrix[i, j] for i in 1:n, j in 1:n if i != j])

global best_cost = typemax(Int)
global best_route = []
global nodes_count = 0

function tsp(curr_city, count, current_cost, visited, route, use_bound)
    global best_cost, best_route, nodes_count
    nodes_count += 1
    
    if count == n
        total_cost = current_cost + cost_matrix[curr_city+1, 1]
        if total_cost < best_cost
            best_cost = total_cost
            best_route = vcat(route, [0])
        end
        return
    end

    for next_city in 0:(n-1)
        if !visited[next_city+1] && cost_matrix[curr_city+1, next_city+1] > 0
            new_cost = current_cost + cost_matrix[curr_city+1, next_city+1]
            
            if use_bound
                remaining_edges = n - count - 1
                lower_bound = new_cost + remaining_edges * c_min
                if lower_bound >= best_cost
                    continue
                end
            end
            
            visited[next_city+1] = true
            push!(route, next_city)
            tsp(next_city, count + 1, new_cost, visited, route, use_bound)
            pop!(route)
            visited[next_city+1] = false
        end
    end
end

println("=== CHẠY BÀI TOÁN NGƯỜI DU LỊCH (JULIA) ===")
println("Cạnh rẻ nhất toàn ma trận c_min = $c_min")

visited = falses(n)
visited[1] = true
global nodes_count = 0
global best_cost = typemax(Int)
global best_route = []
tsp(0, 1, 0, visited, [0], true)
nodes_with_bound = nodes_count
opt_cost = best_cost
opt_route = best_route

visited = falses(n)
visited[1] = true
global nodes_count = 0
global best_cost = typemax(Int)
global best_route = []
tsp(0, 1, 0, visited, [0], false)
nodes_without_bound = nodes_count

println("Chi phí hành trình tối ưu       = $opt_cost")
println("Hành trình tối ưu               = ", join(opt_route, " -> "))
println("Số nút khi CÓ cắt nhánh         = $nodes_with_bound")
println("Số nút khi KHÔNG cắt nhánh      = $nodes_without_bound")