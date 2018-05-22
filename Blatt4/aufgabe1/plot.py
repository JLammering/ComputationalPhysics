import numpy as np
import matplotlib.pyplot as plt


def plotMatrix(matrix, dateiname):

    x = np.arange(0, len(matrix))
    plt.pcolormesh(x, x, matrix)
    plt.colorbar(label='Spin')
    plt.savefig("build/plots/" + dateiname + ".pdf")
    plt.close()


if __name__ == '__main__':
    mat = np.genfromtxt("build/thisisatest.txt", unpack='True')
    plotMatrix(mat, "thisisatest")
