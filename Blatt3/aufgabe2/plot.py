import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, fmin
import uncertainties.unumpy as unp
import matplotlib.colors as colors


def plotMatrix(matrix, dateiname):

    x = np.arange(0, len(matrix))
    plt.pcolormesh(x, x, matrix)
    plt.savefig("build/" + dateiname + ".pdf")
    plt.close()


if __name__ == '__main__':
    # kbT = 1
    matrix = np.genfromtxt('build/kbT=1.txt', unpack='True')
    plotMatrix(matrix, 'kbTgleicheins')
