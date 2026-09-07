board = [
    0 0 0 0 0 6 0 0 0;
    0 0 8 1 0 5 0 4 0;
    0 0 0 9 0 0 7 0 5;
    0 0 0 0 0 9 0 0 0;
    0 0 0 6 0 0 1 0 0;
    0 7 4 0 0 0 0 2 1;
    0 0 0 0 1 3 0 0 0;
    0 0 0 0 0 2 9 0 0;
    0 9 0 0 0 0 8 0 6
]

function is_valid(b, r, c, val)
    for i in 1:9
        if b[r, i] == val || b[i, c] == val
            return false
        end
    end
    start_r, start_c = 3 * div(r - 1, 3) + 1, 3 * div(c - 1, 3) + 1
    for i in 0:2, j in 0:2
        if b[start_r + i, start_c + j] == val
            return false
        end
    end
    return true
end

global count_seq = 0
function solve_seq!(b)
    global count_seq += 1
    for r in 1:9, c in 1:9
        if b[r, c] == 0
            for val in 1:9
                if is_valid(b, r, c, val)
                    b[r, c] = val
                    if solve_seq!(b) return true end
                    b[r, c] = 0
                end
            end
            return false
        end
    end
    return true
end

global count_mrv = 0
function solve_mrv!(b)
    global count_mrv += 1
    min_cand = 10
    best_r, best_c = 0, 0
    
    for r in 1:9, c in 1:9
        if b[r, c] == 0
            cand = sum(is_valid(b, r, c, v) for v in 1:9)
            if cand < min_cand
                min_cand = cand
                best_r, best_c = r, c
            end
        end
    end
    
    if best_r == 0 return true end
    
    for val in 1:9
        if is_valid(b, best_r, best_c, val)
            b[best_r, best_c] = val
            if solve_mrv!(b) return true end
            b[best_r, best_c] = 0
        end
    end
    return false
end

b1 = copy(board)
t_start = time()
solve_seq!(b1)
time_seq = time() - t_start

b2 = copy(board)
t_start = time()
solve_mrv!(b2)
time_mrv = time() - t_start

is_same = (b1 == b2)

println("=== KẾT QUẢ BÀI 4.3 (JULIA) ===")
println("Số lời gọi (Quét tuần tự): $count_seq | (MRV): $count_mrv")
println("Thời gian (Quét tuần tự): $(round(time_seq, digits=4))s | (MRV): $(round(time_mrv, digits=4))s")
println("Lời giải tìm được có giống nhau không? $(is_same ? "Có" : "Không")")