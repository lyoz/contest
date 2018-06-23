from fractions import Fraction

def f(x, suf):
    return int(str(x)+'9'*suf)

def s(n):
    return sum(int(c) for c in str(n))

def g(x, suf):
    n = f(x, suf)
    return Fraction(n,s(n))


res = []
cur=1
x,suf=1,0
while res==[] or res[-1]<=10**15:
    y=x+1
    nxt=g(y,suf)
    if cur<=nxt:
        res.append(f(x,suf))
        x=y
        cur=nxt
    else:
        x=(x-1)//10+1
        suf+=1
        cur=g(x,suf)


k=int(input())
for i in range(k):
    print(res[i])
