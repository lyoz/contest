sx,sy,tx,ty=map(int,input().split())
dx,dy=tx-sx,ty-sy
s1='U'*dy+'R'*dx+'D'*dy+'L'*dx
s2='LU'+'U'*dy+'R'*dx+'RD'+'RD'+'D'*dy+'L'*dx+'LU'
print(s1+s2)
