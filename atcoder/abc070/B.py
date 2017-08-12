a,b,c,d=map(int,input().split())
t=[0]*100
for i in range(a,b):
    t[i]+=1
for i in range(c,d):
    t[i]+=1
print(sum(x==2 for x in t))
