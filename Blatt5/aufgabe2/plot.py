import numpy as np
import matplotlib.pyplot as plt


mat = np.genfromtxt('build/matrix', unpack=True)
plt.pcolormesh(mat)
plt.savefig('build/2a.pdf')
plt.show()
