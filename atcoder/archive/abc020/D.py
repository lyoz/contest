MOD=int(1e9+7)

def get_primes():
    ps=[0,0]+[i for i in range(2,32000)]
    for i in range(2,32000):
        if ps[i]==0:
            continue
        for j in range(i*i,32000,i):
            ps[j]=0
    return [p for p in ps if p]

def get_divisors(k):
    i,ds=1,[]
    while i*i<=k:
        if k%i==0:
            ds.append(i)
            ds.append(k//i)
        i+=1
    return sorted(set(ds))

def get_factors(k,ps):
    i,fs=1,[]
    for p in ps:
        if p*p>k:
            break
        if k%p==0:
            fs.append(p)
        while k%p==0:
            k//=p
    if k>1:
        fs.append(k)
    return fs

def get_sum(a,d,n):
    return (a+a+(n-1)*d)*n//2

def calc(n,k,ps):
    fs=get_factors(k,ps)
    res=0
    for b in range(1<<len(fs)):
        p,s=1,1
        for i,f in enumerate(fs):
            if b>>i&1:
                p,s=p*f,s*-1
        res+=s*get_sum(p,p,n//p)
    return res*k

def solve(n,k):
    ps=get_primes()
    res=0
    for d in get_divisors(k):
        res+=calc(n//d,k//d,ps)*d
    return res%MOD

while 1:
    try:
        n,k=map(int,input().split())
    except: break
    print(solve(n,k))
