while 1:
    try:
        n=int(input())
        a=list(map(int,input().split()))
    except: break

    res=float('inf')
    for p in range(min(a),max(a)+1):
        res=min(res,sum((x-p)**2 for x in a))
    print(res)
