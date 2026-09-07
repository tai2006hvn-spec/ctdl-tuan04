import math

def print_grid_board(sol):
    n = len(sol) - 1
    print(f"\n--- HINH ANH BAN CO CHO n = {n} ---")
    border = "+" + "---+" * n
    print(border)
    for i in range(1, n + 1):
        row_str = "|"
        for j in range(1, n + 1):
            if sol[i] == j:
                row_str += " Q |"
            else:
                row_str += "   |"
        print(row_str)
        print(border)

def solve_n_queens():
    n = int(input("Nhap kich thuoc n: "))
    x = [0] * (n + 1)
    col = [0] * (n + 1)
    dcc = [0] * (2 * n + 1)
    dcp = [0] * (2 * n + 1)
    
    node_count = [0]
    solutions = []

    def backtrack(i):
        node_count[0] += 1
        for j in range(1, n + 1):
            if col[j] == 0 and dcc[i - j + n] == 0 and dcp[i + j] == 0:
                x[i] = j
                col[j] = 1
                dcc[i - j + n] = 1
                dcp[i + j] = 1
                
                if i == n:
                    solutions.append(list(x[1:n+1]))
                else:
                    backtrack(i + 1)
                
                col[j] = 0
                dcc[i - j + n] = 0
                dcp[i + j] = 0

    backtrack(1)
    
    factorial_n = math.factorial(n)
    ratio = node_count[0] / factorial_n

    print(f"Tong so nut da duyet: {node_count[0]}")
    print(f"Tong so loi giai tim duoc: {len(solutions)}")
    print(f"So hoan vi neu vet can (n!): {factorial_n}")
    print(f"Ti le nut / n!: {ratio:.4f}")
    
    if solutions:
        print(f"Loi giai dau tien (mang cot): {solutions[0]}")
        print_grid_board([0] + solutions[0])

if __name__ == "__main__":
    solve_n_queens()