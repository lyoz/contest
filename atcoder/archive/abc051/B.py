k,s=map(int,input().split())
res=0
for x in range(k+1):
    t=s-x
    if t<0:
        continue
    ymin=max(t-k,0)
    ymax=min(t,k)
    res+=max(ymax-ymin+1,0)
print(res)
