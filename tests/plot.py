#!/usr/bin/python3

import sys
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import pandas

def plot(ax, filename, color):
    points = pandas.read_csv(filename, delimiter=';')

    x = points['x'].values
    y = points['y'].values
    z = points['dose'].values

    ax.scatter(x, y, z, c=color, marker='o')

if len(sys.argv) != 3:
    print("filenames should be specified")
    exit()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

filename = sys.argv[1]
print("irregular data filename = " + filename)

plot(ax, filename, 'r')

filename = sys.argv[2]
print("regular data filename = " + filename)

plot(ax, filename, 'g')

plt.show()