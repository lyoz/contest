n,m=map(int,input().split())
xs,ys=[],[]
for _ in range(m):
    x,y=map(int,input().split())
    xs.append(x-1)
    ys.append(y-1)

dst=[[i for i in range(n)] for _ in range(1<<n)]
for b in range(1<<n):
    for x,y in zip(xs,ys):
        if not b>>x&1:
            dst[b][y]=-1
    dst[b]=[i for i in dst[b] if i!=-1 and not b>>i&1]

dp=[0]*(1<<n)
dp[0]=1
for b,x in enumerate(dp):
    if x==0:
        continue
    for i in dst[b]:
        dp[b|1<<i]+=x
print(dp[-1])
