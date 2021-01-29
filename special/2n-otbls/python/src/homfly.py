import sympy

n, v, z = sympy.symbols('n v z')

class link():
    def __init__(self):
        self.string = 'trivial'
        self.homfly = 1

def cri1(s):
    if s[0] == s[1] == s[2] == '0' or\
       s[6] == s[7] == s[8] == '0' or\
       s[0] == s[3] == s[5] == s[6] == '0' or\
       s[1] == s[3] == s[4] == s[7] == '0' or\
       s[2] == s[4] == s[5] == s[8] == '0':
        return True
    else:
        return False
    
def cri2(s):
    if s[0] == s[1] == s[4] == s[5] == s[8] == '0' or\
       s[1] == s[2] == s[3] == s[5] == s[6] == '0' or\
       s[0] == s[2] == s[3] == s[4] == s[7] == '0' or\
       s[0] == s[3] == s[5] == s[7] == s[8] == '0' or\
       s[1] == s[3] == s[4] == s[6] == s[8] == '0' or\
       s[2] == s[4] == s[5] == s[6] == s[7] == '0':
        return True
    else:
        return False
    
def cri3(s):
    if s[0] == s[1] == s[2] == s[6] == s[7] == s[8] == '0' or\
       s[0] == s[1] == s[2] == s[3] == s[5] == s[6] == '0' or\
       s[0] == s[1] == s[2] == s[3] == s[4] == s[7] == '0' or\
       s[0] == s[1] == s[2] == s[4] == s[5] == s[8] == '0' or\
       s[0] == s[3] == s[5] == s[6] == s[7] == s[8] == '0' or\
       s[1] == s[3] == s[4] == s[6] == s[7] == s[8] == '0' or\
       s[2] == s[4] == s[5] == s[6] == s[7] == s[8] == '0':
        return True
    else:
        return False

bls = []
for q in range(2 ** 9):
    bl = link()
    bl.string = "{0:09b}".format(q)
    nz = bl.string.count('0')
    
    nc = 0
    if nz <= 2: nc = 6 - nz
    elif nz >= 3 and nz <= 4:
        nc = (8 - nz) if cri1(bl.string) else (6 - nz)
    elif nz == 5:
        nc = (8 - nz) if cri1(bl.string) or cri2(bl.string) else (6 - nz)
    elif nz == 6:
        nc = (nz - 2) if cri3(bl.string) else (nz - 4)
    elif 7 <= nz <= 9: nc = nz - 4
    
    bl.homfly = 1 if nc == 1 else ((v**(-1) - v) * z**(-1))**(nc - 1)
    bls.append(bl)

def multiplier(tangle, theta):
    if 'h' in tangle and theta == '1':
        return v**(2 * n)
    elif 'h' in tangle and theta == '0':
        return (v * z * (1 - v**(2 * n))) / (1 - v**2)
    elif 'v' in tangle and theta == '1':
        return (z * (1 - v**(-2 * n))) / (v**(-1) - v)
    elif 'v' in tangle and theta == '0':
        return v**(-2 * n)

def weight(otbl, bl):
    w = 1
    for tangle, theta in zip(otbl.string, bl.string):
        w *= multiplier(tangle, theta)
    return w

def homfly_for_even_cross_otbl(otbl):
    polynomial = 0
    for bl in bls:
        polynomial += weight(otbl, bl) * bl.homfly
    return polynomial

if __name__ == '__main__':
    otbl = link()
    otbl.string = "ah ah av ah ah ah ah av av".split()
    otbl.homfly = homfly_for_even_cross_otbl(otbl)