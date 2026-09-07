function print_grid_board(sol)
    n = length(sol)
    println("\n--- HINH ANH BAN CO CHO n = $n ---")
    border = "+" * repeat("---+", n)
    println(border)
    for i in 1:n
        row_str = "|"
        for j in 1:n
            if sol[i] == j
                row_str *= " Q |"
            else
                row_str *= "   |"
            end
        end
        println(row_str)
        println(border)
    end
end

function solve_n_queens()
    print("Nhap kich thuoc n: ")
    n = parse(Int, readline())
    
    x = zeros(Int, n)
    col = zeros(Int, n)
    dcc = zeros(Int, 2 * n)
    dcp = zeros(Int, 2 * n)
    
    node_count = [0]
    solutions = Vector{Int}[]

    function backtrack(i)
        node_count[1] += 1
        for j in 1:n
            if col[j] == 0 && dcc[i - j + n] == 0 && dcp[i + j] == 0
                x[i] = j
                col[j] = 1
                dcc[i - j + n] = 1
                dcp[i + j] = 1
                
                if i == n
                    push!(solutions, copy(x))
                else
                    backtrack(i + 1)
                end
                
                col[j] = 0
                dcc[i - j + n] = 0
                dcp[i + j] = 0
            end
        end
    end

    backtrack(1)
    
    total_nodes = node_count[1]
    factorial_n = factorial(big(n))
    ratio = total_nodes / factorial_n

    println("Tong so nut da duyet: $total_nodes")
    println("Tong so loi giai tim duoc: $(length(solutions))")
    println("So hoan vi neu vet can (n!): $factorial_n")
    println("Ti le nut / n!: $(round(ratio, digits=4))")

    if !isempty(solutions)
        println("Loi giai dau tien (mang cot): $(solutions[1])")
        print_grid_board(solutions[1])
    end
end

solve_n_queens()