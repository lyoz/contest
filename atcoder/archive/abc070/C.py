from functools import reduce

def gcd(a,b):
    while b:
        a,b=b,a%b
    return a

def lcm(a,b):
    return a//gcd(a,b)*b

n=int(input())
a=[int(input()) for _ in range(n)]

print(reduce(lcm,a))
