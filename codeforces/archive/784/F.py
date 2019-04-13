import time

a=list(map(int,input().split()))[1:]
print(' '.join(map(str,sorted(a))))

t0=time.clock();
while time.clock()-t0<1.5:
    pass
