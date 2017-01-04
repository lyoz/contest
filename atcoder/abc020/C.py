import heapq

def calc(h,w,grid,x):
    vis=[[None]*w for i in range(h)]
    q=[]
    for i in range(h):
        for j in range(w):
            if grid[i][j]=='S':
                heapq.heappush(q,(0,i,j))
    di,dj=[-1,1,0,0],[0,0,-1,1]
    while len(q):
        cx,ci,cj=heapq.heappop(q)
        if vis[ci][cj] is not None:
            continue
        vis[ci][cj]=cx
        for k in range(4):
            ni,nj=ci+di[k],cj+dj[k]
            if not (0<=ni<h and 0<=nj<w):
                continue
            nx=cx+(x if grid[ni][nj]=='#' else 1)
            heapq.heappush(q,(nx,ni,nj))
    for i in range(h):
        for j in range(w):
            if grid[i][j]=='G':
                return vis[i][j]

while 1:
    try:
        h,w,t=map(int,input().split())
    except: break
    grid=[list(input()) for _ in range(h)]

    lo,hi=1,int(1e9)

    while lo<hi:
        mi=(lo+hi)//2
        if calc(h,w,grid,mi)>t:
            hi=mi
        else:
            lo=mi+1

    print(lo-1)
