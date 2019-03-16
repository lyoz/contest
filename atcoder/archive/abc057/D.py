from fractions import Fraction

def choose(n,r):
    res=1
    for i in range(r):
        res=res*(n-i)//(i+1)
    return res

n,a,b=map(int,input().split())
vs=sorted(map(int,input().split()))

average_max=Fraction(sum(vs[n-a:]),a)
print("{0:.9f}".format(float(average_max)))

res=0
for m in range(a,b+1):
    average=Fraction(sum(vs[n-m:]),m)
    if average<average_max:
        continue
    mn=min(vs[n-m:])
    res+=choose(sum(1 for x in vs if x==mn),
                sum(1 for x in vs[n-m:] if x==mn))
print(res)
