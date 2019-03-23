import math

n=int(input())

res=float('inf')
for i in range(1,int(math.sqrt(n))+10):
    if n%i==0:
        res=min(res,max(len(str(i)),len(str(n//i))))
print(res)
