MOD = 998244353

while True:
    try:
        n = int(input())
    except:
        break

    res = 0
    i = 1
    while i <= n:
        a = i - (i - 1)
        b = min(i * 10 - 1, n) - (i - 1)
        res += (a + b) * (b - a + 1) // 2
        i *= 10
    print(res % MOD)
