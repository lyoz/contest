from collections import defaultdict

n,ma,mb=map(int,input().split())
f=defaultdict(lambda:float('inf'))
for _ in range(n):
    a,b,c=map(int,input().split())
    t=f.copy()
    t[a,b]=min(t[a,b],c)
    for k,v in f.items():
        ka,kb=k[0]+a,k[1]+b
        t[ka,kb]=min(t[ka,kb],v+c)
    f=t

costs=[f[a,b] for a,b in f if a*mb==b*ma]
print(min(costs) if costs else -1)
