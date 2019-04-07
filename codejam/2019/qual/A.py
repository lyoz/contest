def solve():
    n = int(input())

    a = list(str(1)[::-1])
    b = list(str(n - 1)[::-1])
    while len(a) < len(b):
        a.append("0")
    for i in range(len(a)):
        if b[i] == "4":
            a[i] = str(int(a[i]) + 1)
            b[i] = str(int(b[i]) - 1)
    x = int("".join(reversed(a)))
    y = int("".join(reversed(b)))
    print(x, y)


n = int(input())
for i in range(n):
    print("Case #{}: ".format(i + 1), end="")
    solve()
