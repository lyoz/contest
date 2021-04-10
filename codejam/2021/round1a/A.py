def solve(a):
    n = len(a)
    b = [a[0]]
    res = 0
    for i in range(1, n):
        if a[i] > b[-1]:
            b.append(a[i])
            continue
        if str(b[-1]).startswith(str(a[i])):
            x = b[-1] + 1
            if str(x).startswith(str(a[i])):
                res += len(str(x)) - len(str(a[i]))
                b.append(x)
                continue
        x = a[i]
        while x <= b[-1]:
            x *= 10
            res += 1
        b.append(x)
    print(res)


tc = int(input())

for i in range(tc):
    n = int(input())
    a = [int(x) for x in input().split()]
    print(f"Case #{i+1}: ", end="")
    solve(a)
