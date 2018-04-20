import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, fmin
import uncertainties.unumpy as unp


def plotRN(N, R_N):

    def func(n, a, e):
        return(a * n**(e))

    # fit an ermittelten daten
    popt, pcov = curve_fit(func, N, R_N)
    n_plot = np.linspace(min(N) - 30, max(N + 30), 10000)
    plt.plot(N, R_N, 'kx', label='Messwerte')
    plt.plot(n_plot, func(n_plot, *popt), label='fit :a N^e ; [a, e] = ' + str(popt) )
    # plt.plot(n_plot, func(n_plot, popt[0], 0.75, popt[2]), label='so waere es richtig')
    # plt.plot(N**(0.25), R_N, 'kx', label='Messwerte')
    # plt.xlabel(r'$N^{0.25}$')
    plt.xlabel(r'$N$')
    plt.xlim(min(N) - 5, max(N) + 5)
    plt.ylim(min(R_N) - 5, max(R_N) + 5)
    plt.ylabel(r'$R_N$')
    plt.legend(loc='best')
    # in matplotlibrc leider (noch) nicht möglich
    plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
    plt.savefig('plot.pdf')
    plt.close()


if __name__ == '__main__':
    N, R_N = np.genfromtxt('mittlClustergroesse.txt', unpack='True')
    plotRN(N, R_N)
