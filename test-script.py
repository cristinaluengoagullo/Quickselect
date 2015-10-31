#!/usr/bin/python

import subprocess
import math

def sampleKs (n):
  nSqrt = math.sqrt(n)
  ks = set()
  ks.add(n/2)
  i = int(nSqrt)
  while (i < (n-nSqrt)):
      ks.add(i)
      i += int(float(1)/5*(n-2*nSqrt))
  ks = sorted(ks)
  return ks

#lengths = [1000,2000,5000,7000,10000,20000,50000,70000,100000,200000,500000]
lengths = [1000]
print "**** Quickselect deterministic pivot ****"
for i in range(0,len(lengths)):
    print "length = " + str(lengths[i])
    ks = sampleKs(lengths[i])
    print "ks = " + str(ks)
    for j in range(0,len(ks)):
        args = ['./main','-norep','-det',str(lengths[i]),str(ks[j])]
        subprocess.call(args)
    print "------------------------"
print "**** Quickselect random pivot ****"
for i in range(0,len(lengths)):
    print "length = " + str(lengths[i])
    ks = sampleKs(lengths[i])
    print "ks = " + str(ks)
    for j in range(0,len(ks)):
        args = ['./main','-norep','-rand',str(lengths[i]),str(ks[j])]
        subprocess.call(args)
    print "------------------------"
print "**** Quickselect median of medians pivot ****"
for i in range(0,len(lengths)):
    print "length = " + str(lengths[i])
    ks = sampleKs(lengths[i])
    print "ks = " + str(ks)
    for j in range(0,len(ks)):
        args = ['./main','-norep','-mom',str(lengths[i]),str(ks[j])]
        subprocess.call(args)
    print "------------------------"
print "**** Monte Carlo ****"
for i in range(0,len(lengths)):
    print "length = " + str(lengths[i])
    ks = sampleKs(lengths[i])
    print "ks = " + str(ks)
    for j in range(0,len(ks)):
        print ks[j]
        args = ['./main','-norep','-monte',str(lengths[i]),str(ks[j])]
        subprocess.call(args)
    print "------------------------"
