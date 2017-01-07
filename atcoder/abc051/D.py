def used(dp,u,v,w):
    n=len(dp)
    for i in range(n):
        for j in range(i+1,n):
            if dp[i][j]==dp[i][u]+w+dp[v][j] or dp[i][j]==dp[i][v]+w+dp[u][j]:
                return True
    return False

while 1:
    try:
        n,m=map(int,input().split())
        es=[]
        for _ in range(m):
            u,v,w=map(int,input().split())
            es.append((u-1,v-1,w))
    except: break

    dp=[[float('inf')]*n for _ in range(n)]
    for i in range(n):
        dp[i][i]=0
    for u,v,w in es:
        dp[u][v]=dp[v][u]=w
    for k in range(n):
        for i in range(n):
            for j in range(n):
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j])
    print(sum(int(not used(dp,u,v,w)) for u,v,w in es))
