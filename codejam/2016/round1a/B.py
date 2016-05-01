def solve():
    n=int(input())
    f={}
    for _ in range(2*n-1):
        for x in map(int,input().split()):
            f[x]=f.get(x,0)+1
    print(' '.join(map(str,sorted(k for k,v in f.items() if v%2==1))))

for i in range(int(input())):
    print('Case #{}: '.format(i+1),end='')
    solve()
