import matplotlib.patches as patches 
import matplotlib.pyplot as plt 
from sys import argv

points = list(map(lambda s : tuple(map(float, s.split())), open(argv[1]).readlines()[1:]))
triangles = list(map(
                    lambda s : tuple(map(lambda x : int(x) - 1, s.split())), 
                    open(argv[2]).readlines()[1:]))

x = []
y = []

for t in triangles:
    for v in t:
        x.append(points[v][0])
        y.append(points[v][1])
    x.append(points[t[0]][0])
    y.append(points[t[0]][1])
    x.append(None)
    y.append(None)

plt.plot(x, y)
plt.axis("equal")

plt.show() 

