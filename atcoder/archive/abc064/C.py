from collections import defaultdict

n=int(input())
a=sorted(map(int,input().split()))

s=defaultdict(int)
wild=0
for x in a:
    if x>=3200:
        wild+=1
    else:
        s[x//400]+=1

mn=len(s)+(len(s)==0)
mx=len(s)+wild

print(mn,mx)
