def solve(n, a):
    if a == ['.'*n]*n:
        return -1
    white_column = sum(any(a[j][i] == '.' for j in range(n)) for i in range(n))
    res = float('inf')
    for r in range(n):
        all_white = all(a[i][r] == '.' for i in range(n))
        res = min(res, white_column + all_white + sum(1 for i in range(n) if a[r][i] == '.'))
    return res


n = int(input())
a = [input() for _ in range(n)]
print(solve(n, a))
