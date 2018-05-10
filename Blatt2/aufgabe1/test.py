from __future__ import division
from matplotlib.patches import Patch
from pylab import *

def func3(x,y):
    return (1- x/2 + x**5 + y**3)*exp(-x**2-y**2)


# make these smaller to increase the resolution
dx, dy = 0.05, 0.05

x = arange(-3.0, 3.0001, dx)
y = arange(-3.0, 3.0001, dy)
X,Y = meshgrid(x, y)

Z = func3(X, Y)
pcolor(X, Y, Z, cmap=cm.RdBu, vmax=abs(Z).max(), vmin=-abs(Z).max())
colorbar()
axis([-3,3,-3,3])

show()
