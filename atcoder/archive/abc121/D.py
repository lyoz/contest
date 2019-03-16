def g(x):
    if x % 4 == 0:
        return x
    elif x % 4 == 1:
        return 1
    elif x % 4 == 2:
        return x + 1
    elif x % 4 == 3:
        return 0


def f(a, b):
    res = g(b)
    if a > 0:
        res ^= g(a - 1)
    return res


a, b = map(int, input().split())
print(f(a, b))
