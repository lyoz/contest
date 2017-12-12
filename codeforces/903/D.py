from collections import defaultdict

n=int(input())
a=map(int,input().split())

f,s,res=defaultdict(int),0,0
for cnt,x in enumerate(a,start=1):
    f[x]+=1
    s+=x;
    res+=x*cnt-s-f[x-1]+f[x+1]

print(res)
