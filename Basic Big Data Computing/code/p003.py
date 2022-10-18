import pyspark
from pyspark import SparkContext
from pyspark import SparkFiles
import math

def calcost(g0, aa):
    env = 0
    for d in g0:
        for a in aa:
            if a.value < d.value:
                env += a.value
    return env
def calmp(aa,b0):
    env = 0
    for a in aa:
        if a.value < b0:
            env += math.log(a.value,2)*math.e
    return env

def finmaxp(cp):
    i = cp[0]
    for j in range(len(cp)):
        if cp[j]>i:
            i = cp[j]
    return i,cp[i]
def finmaxp2(ct):
    i = ct[0]
    for j in range(len(ct)):
        if ct[j]>i:
            i = ct[j]
    return ct[i]
def judgeparent(fra,frb):
    f0 = True
    for i in frb:
        ff = False
        if i.pre in fra:
            ff = True
        f0 = f0 and ff
    return f0
def con(aa,g0):
    for d in g0:
        if aa.value == d.value:
            return d


def calculate003(graph0,numk,nums,numb):
    ki = []
    for i in range(1 + math.ceil(math.log(numk,2))):
        if i==math.ceil(math.log(numk,2)):
            ki.append(numk)
        else:
            ki.append(2**numk)
    
    cop1 = 0
    for i in range(1 + math.ceil(math.log(numk,2))):
        cop2+=ki[i]

    b0 = 1
    while True:
        solution = []
        consider = []
        visited = []
        ct = []
        cp = []
        for p in graph0:
            a1 = calcost(p,graph0)
            a2 = calmp(p,b0)
            ct.append(a1)
            consider.append(p)
            cp.append(a2)
        rem = nums*(1-1/math.e)
        countnum = []
        for i in range(math.ceil(math.log(numk,2))):
            countnum.append(0)
        cop2 = 0
        for i in range(math.ceil(math.log(numk,2))):
            cop2+=countnum[i]
        if len(consider)>0 and cop2<=cop1:
            ba, aa = finmaxp(cp)
            consider.remove(aa)
            countnum[ba] += 1
            if ba>=0 and countnum[ba]<=ki[ba]:
                solution.append(aa)
            rem -= len(cp)
            if rem < 0:
                return solution
            for p in consider:
                cp.remove(con(aa,graph0))
        else:
            visited.append(con(p,graph0))
            for m in cp:
                if judgeparent(m,graph0):
                    consider.append(m)

        b0 = b0*(1+numb)
        if b0 > finmaxp2(ct):
            break


