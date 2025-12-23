import numpy as np
import matplotlib.pyplot as plot

x=[1,3,5,7,8,9,10,12,13]
y=[50,-30,-20,20,5,1,30,80,-10]


def f(o):
  sum = 0
  n=len(x)-1

  for i in range(n+1):
    prod = y[i]
    for j in range(n+1):
      if i!= j:
        prod=prod*(o-x[j])/(x[i]-x[j])
    sum = sum + prod
  return sum

x=[1,3,5,7,8,9,10,12,13,14]
y=[50,-30,-20,20,5,1,30,80,-10,-11]
prange = np.linspace(min(x),max(x),500)

plot.plot(prange,f(prange))
plot.show()
