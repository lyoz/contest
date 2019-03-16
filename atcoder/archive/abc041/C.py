n=int(input())
a=map(int,input().split())
for x,i in sorted([(x,i) for i,x in enumerate(a)], reverse=True):
    print(i+1)
