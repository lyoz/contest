while 1:
    try:
        n=int(input())
    except:
        break
    for s in map(str,range(1000)):
        if n<len(s):
            print(s[n])
            break;
        else:
            n-=len(s)
