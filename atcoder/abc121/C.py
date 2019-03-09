n, m = map(int, input().split())
ts = sorted((tuple(map(int, input().split()))) for _ in range(n))
res = 0
for a, b in ts:
    x = min(b, m)
    res += a * x
    m -= x
print(res)
