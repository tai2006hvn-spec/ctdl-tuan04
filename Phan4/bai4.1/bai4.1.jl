mutable struct Item
    name::String
    weight::Int
    value::Int
    ratio::Float64
end

function solve_knapsack(raw_items, W, enable_pruning=true)
    items = copy(raw_items)
    sort!(items, by = x -> x.ratio, rev=true)
    n = length(items)
    
    best_val = [0]
    best_comb = String[]
    node_count = [0]
    
    function bound(i, weight, value)
        b = Float64(value)
        total_w = weight
        j = i
        while j <= n && total_w + items[j].weight <= W
            total_w += items[j].weight
            b += items[j].value
            j += 1
        end
        if j <= n
            b += (W - total_w) * items[j].ratio
        end
        return b
    end

    function backtrack(i, current_w, current_v, current_items)
        node_count[1] += 1
        if current_w <= W && current_v > best_val[1]
            best_val[1] = current_v
            empty!(best_comb)
            append!(best_comb, current_items)
        end
        
        if i > n return end
        
        if enable_pruning
            if bound(i, current_w, current_v) <= best_val[1]
                return
            end
        end
        
        if current_w + items[i].weight <= W
            push!(current_items, items[i].name)
            backtrack(i + 1, current_w + items[i].weight, current_v + items[i].value, current_items)
            pop!(current_items)
        end
        
        backtrack(i + 1, current_w, current_v, current_items)
    end

    backtrack(1, 0, 0, String[])
    return best_val[1], best_comb, node_count[1]
end

raw_items = [
    Item("A", 4, 19, 19.0/4), Item("B", 7, 25, 25.0/7), Item("C", 3, 7, 7.0/3),
    Item("D", 3, 8, 8.0/3), Item("E", 3, 9, 9.0/3), Item("F", 10, 21, 21.0/10)
]
W = 14

val_co, comb_co, nodes_co = solve_knapsack(raw_items, W, true)
val_khong, comb_khong, nodes_khong = solve_knapsack(raw_items, W, false)

println("So nut khi CO cat nhanh: $nodes_co")
println("So nut khi KHONG cat nhanh: $nodes_khong")
println("So nut giam duoc: $(round(nodes_khong / nodes_co, digits=2)) lan")