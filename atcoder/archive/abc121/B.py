n, m, c = map(int, input().split())
b = list(map(int, input().split()))
res = 0
for _ in range(n):
    a = list(map(int, input().split()))
    res += sum(a[i] * b[i] for i in range(m)) + c > 0
print(res)
