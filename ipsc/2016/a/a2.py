def overwrap(s1,s2):
    for i in range(4):
        if(s1[i:]==s2[:4-i]):
            return s1+s2[4-i:]
    return ""

def solve(ss):
    for i in range(10):
        for j in range(10):
            if i==j: continue
            o=overwrap(ss[i],ss[j])
            if not o: continue
            res=o+''.join(ss[k] for k in range(10) if k!=i and k!=j)
            return res+'X'*(39-len(res))

n=int(input())
for _ in range(n):
    input()
    ss=input().split(' ')
    print(solve(ss))
