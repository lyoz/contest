from collections import deque

INF=float('inf')

n=int(input())
g=[[] for _ in range(n)]
for _ in range(n-1):
    u,v,w=map(int,input().split())
    g[u-1].append((v-1,w))
    g[v-1].append((u-1,w))

q,k=map(int,input().split())
ds=[INF]*n
que=deque([(k-1,0)])
while len(que):
    u,d=que.popleft()
    if ds[u]!=INF:
        continue
    ds[u]=d
    for v,w in g[u]:
        que.append((v,d+w))

for _ in range(q):
    u,v=map(int,input().split())
    print(ds[u-1]+ds[v-1])
