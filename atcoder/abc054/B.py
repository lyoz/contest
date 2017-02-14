n,m=map(int,input().split())
a=[input() for _ in range(n)]
b=[input() for _ in range(m)]

res=any([r[j:j+m] for r in a[i:i+m]]==b for i in range(n-m+1) for j in range(n-m+1))
print('Yes' if res else 'No')
