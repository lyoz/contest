c=[input() for _ in range(2)]

res=True
for i in range(2):
    for j in range(3):
        res&=c[i][j]==c[1-i][2-j]
print('YES' if res else 'NO')
