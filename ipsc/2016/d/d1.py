import sys

colors=['red','orange','yellow','green','blue','pink']
shapes=['square','wide rectangle']

coord_dict={}
coord_dict['red']=('75 76','291 76')
coord_dict['orange']=('177 171','503 174')
coord_dict['yellow']=('166 78','509 81')
coord_dict['green']=('81 170','281 171')
coord_dict['blue']=('79 264','282 262')
coord_dict['pink']=('170 274','514 280')

def get_coord(cmd):
    color,index=[(c,i) for c in colors for i in range(2) if c+' '+shapes[i] in cmd][0]
    return coord_dict[color][index]

print('1 1')
for line in sys.stdin:
    print('next')
    coords=[get_coord(cmd) for cmd in line.split('and then')]
    print('\n'.join(coords))
print('done')
