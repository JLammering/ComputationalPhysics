import numpy as np
import matplotlib.pyplot as plt


def plotMatrix(matrix, dateiname):

    x = np.arange(0, len(matrix))
    plt.pcolormesh(x, x, matrix)
    plt.colorbar(label='Spin')
    plt.savefig("build/plots/" + dateiname + ".pdf")
    plt.close()


if __name__ == '__main__':

    anzahl_steps = 10
    for i in range(anzahl_steps):
        mat = np.genfromtxt("build/2DTESTRUN"+str(i)+".txt", unpack='True')
        plotMatrix(mat, "2DTESTRUN"+str(i))
