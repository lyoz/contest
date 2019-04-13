while 1:
    try:
        n=int(input())
        s=input()
    except: break;
    print(-1 if n>26 else n-len(set(s)))
