import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, fmin
import uncertainties.unumpy as unp


def plotRN(N, R_N):
    plt.plot(N**(0.25), R_N, 'kx', label='Messwerte')
    plt.xlabel(r'$N^{0.25}$')
    plt.ylabel(r'$R_N$')
    plt.legend(loc='best')

    # in matplotlibrc leider (noch) nicht möglich
    plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
    plt.savefig('plot.pdf')
    plt.close()


if __name__ == '__main__':
    N, R_N = np.genfromtxt('mittlClustergroesse.txt', unpack='True')
    plotRN(N, R_N)
