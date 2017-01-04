MOD=int(1e9+7)

def gcd(a,b):
    return gcd(b,a%b) if b else a

def lcm(a,b):
    return a//gcd(a,b)*b

# a + a+d + ... + a+(n-1)d
def get_sum(a,n,d):
    return a*n+d*(n-1)*n//2

# get primes \in [0,n)
def get_primes(n):
    res=[0]*n
    for i in range(2,n):
        res[i]=i
    for i in range(2,n):
        if res[i]:
            for j in range(i*i,n,i):
                res[j]=0
    return [x for x in res if x!=0]

# get divisors for n
def get_divisors(n):
    res=[]
    i=1
    while i*i<=n:
        if n%i==0:
            res.extend((i,n//i))
        i+=1
    return sorted(set(res))

# get factors for n
def get_factors(n,ps):
    res=[]
    for p in ps:
        if p*p>n:
            break
        if n%p==0:
            res.append(p)
        while n%p==0:
            n//=p
    if n>1:
        res.append(n)
    return res

def calc(n,k,ps):
    fs=get_factors(k,ps)
    res=0
    for b in range(1<<len(fs)):
        p,s=1,1
        for i,f in enumerate(fs):
            if b>>i&1:
                p*=f
                s*=-1
        res+=s*get_sum(p,n//p,p)
    return res*k

def solve(n,k):
    ps=get_primes(50000)
    ds=get_divisors(k)
    return sum(d*calc(n//d,k//d,ps) for d in ds)%MOD

while 1:
    try:
        n,k=map(int,input().split())
    except: break
    print(solve(n,k))
