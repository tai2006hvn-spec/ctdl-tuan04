import time
import copy

# Đề Sudoku mục E (56 ô trống được điền số 0)
board = [
    [0, 0, 0, 0, 0, 6, 0, 0, 0],
    [0, 0, 8, 1, 0, 5, 0, 4, 0],
    [0, 0, 0, 9, 0, 0, 7, 0, 5],
    [0, 0, 0, 0, 0, 9, 0, 0, 0],
    [0, 0, 0, 6, 0, 0, 1, 0, 0],
    [0, 7, 4, 0, 0, 0, 0, 2, 1],
    [0, 0, 0, 0, 1, 3, 0, 0, 0],
    [0, 0, 0, 0, 0, 2, 9, 0, 0],
    [0, 9, 0, 0, 0, 0, 8, 0, 6]
]

def is_valid(b, r, c, val):
    for i in range(9):
        if b[r][i] == val or b[i][c] == val:
            return False
    start_r, start_c = 3 * (r // 3), 3 * (c // 3)
    for i in range(3):
        for j in range(3):
            if b[start_r + i][start_c + j] == val:
                return False
    return True

# 1. Quét tuần tự
count_seq = 0
def solve_sequential(b):
    global count_seq
    count_seq += 1
    for r in range(9):
        for c in range(9):
            if b[r][c] == 0:
                for val in range(1, 10):
                    if is_valid(b, r, c, val):
                        b[r][c] = val
                        if solve_sequential(b):
                            return True
                        b[r][c] = 0
                return False
    return True

# 2. Heuristic MRV
count_mrv = 0
def solve_mrv(b):
    global count_mrv
    count_mrv += 1
    
    min_cand = 10
    best_r, best_c = -1, -1
    for r in range(9):
        for c in range(9):
            if b[r][c] == 0:
                cand = sum(1 for val in range(1, 10) if is_valid(b, r, c, val))
                if cand < min_cand:
                    min_cand = cand
                    best_r, best_c = r, c
                    
    if best_r == -1:
        return True
        
    for val in range(1, 10):
        if is_valid(b, best_r, best_c, val):
            b[best_r][best_c] = val
            if solve_mrv(b):
                return True
            b[best_r][best_c] = 0
    return False

# Thực thi và đo đạc
b1 = copy.deepcopy(board)
t0 = time.time()
solve_sequential(b1)
t1 = time.time()
time_seq = t1 - t0

b2 = copy.deepcopy(board)
t0 = time.time()
solve_mrv(b2)
t1 = time.time()
time_mrv = t1 - t0

is_same = (b1 == b2)

print("=== KẾT QUẢ BÀI 4.3 (PYTHON) ===")
print(f"Số lời gọi (Quét tuần tự): {count_seq} | (MRV): {count_mrv}")
print(f"Thời gian (Quét tuần tự): {time_seq:.4f}s | (MRV): {time_mrv:.4f}s")
print(f"Lời giải tìm được có giống nhau không? {'Có' if is_same else 'Không'}")