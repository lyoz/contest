a,b=map(int,input().split())
a,b=(a+11)%13,(b+11)%13
if a==b:
    print('Draw')
elif a>b:
    print('Alice')
else:
    print('Bob')
