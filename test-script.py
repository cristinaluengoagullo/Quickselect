#!/usr/bin/python

import subprocess
import math

def sampleKs (n):
  nSqrt = math.sqrt(n)
  ks = set()
  ks.add(n/2)
  i = nSqrt
  while (i < (n-nSqrt)):
      ks.add(i)
      i += int(float(1)/10*(n-2*nSqrt))
  ks = sorted(ks)
  return ks

ks = sampleKs(100)
for i in range(0,len(ks)):
    args = ['./main', '-rep','-det','1000',str(ks[i])]
    subprocess.call(args)
