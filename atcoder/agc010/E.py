import sys
sys.setrecursionlimit(10**9)

def gcd(a: int, b:int):
    while b:
        a,b=b,a%b
    return a

def merge(a,us,vs):
    i,j,res=0,0,[]
    while i<len(us) and j<len(vs):
        if a[us[i]]>=a[vs[j]]:
            res.append(us[i])
            i+=1
        else:
            res.append(vs[j])
            j+=1
    return res+us[i:]+vs[j:]

def dfs(g,a,u,vis):
    vis[u]=True
    res=[]
    for v in g[u]:
        if not vis[v]:
            res=merge(a,res,dfs(g,a,v,vis))
    return [u]+res

while 1:
    try:
        n=int(input())
        a=sorted(map(int,input().split()))
    except: break

    g=[[] for _ in range(n)]
    for i in range(n):
        for j in range(i+1,n):
            if gcd(a[i],a[j])!=1:
                g[i].append(j)
                g[j].append(i)

    vis=[False]*n
    res=[]
    for u in range(n):
        if not vis[u]:
            res=merge(a,res,dfs(g,a,u,vis))
    print(' '.join(str(a[u]) for u in res))
