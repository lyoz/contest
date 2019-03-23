n,m=map(int,input().split())
a,b=[0]*n,[0]*n
for i in range(n):
    a[i],b[i]=map(int,input().split())
c,d=[0]*m,[0]*m
for i in range(m):
    c[i],d[i]=map(int,input().split())

for i in range(n):
    res=min(range(m),key=lambda j:abs(a[i]-c[j])+abs(b[i]-d[j]))
    print(res+1)
