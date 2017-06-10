n=int(input())
s=input()

op,cl=0,0
for c in s:
    if c=='(':
        op+=1
    else:
        if op>0:
            op-=1
        else:
            cl+=1
print(('('*cl)+s+(')'*op))
