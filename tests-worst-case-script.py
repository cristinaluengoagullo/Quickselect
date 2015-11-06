#!/usr/bin/python

import subprocess
import math

lengths = [10001,50001,100001,500001,1000001,5000001,10000001,50000001,100000001]
for i in range(0,len(lengths)):
  print ""
  k = lengths[i]/2
  args = ['./main','-wc',str(lengths[i])]
  subprocess.call(args)
  print""
