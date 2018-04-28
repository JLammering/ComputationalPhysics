import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, fmin
import uncertainties.unumpy as unp


def plotHisto(rnd, dateiname, m):

    plt.hist(rnd, bins=10)
    plt.xlabel(r'$bin$')
    plt.ylabel(r'$Häufigkeit$')
    # in matplotlibrc leider (noch) nicht möglich
    plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
    plt.savefig("build/"+dateiname+"Hist.pdf")
    plt.close()

    plt.scatter(rnd[:min(m, 100000)-1], rnd[1:min(m, 100000)])
    plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
    plt.savefig("build/"+dateiname+"Scatter.pdf")
    plt.close()


if __name__ == '__main__':
    rnd_1 = np.genfromtxt('build/ersterGenerator.txt', unpack='True')
    plotHisto(rnd_1, "erster", 6075)

    rnd_2 = np.genfromtxt('build/zweiterGenerator.txt', unpack='True')
    plotHisto(rnd_2, "zweiter", 256)

    rnd_3 = np.genfromtxt('build/dritterGenerator.txt', unpack='True')
    plotHisto(rnd_3, "dritter", 2147483648)

    rnd_4 = np.genfromtxt('build/vierterGenerator.txt', unpack='True')
    plotHisto(rnd_4, "vierter", 2147483647)

    rnd_5 = np.genfromtxt('build/fifthGenerator.txt', unpack='True')
    plotHisto(rnd_5, "fifth", 100000)

    rnd_6 = np.genfromtxt('build/sixGenerator.txt', unpack='True')
    plotHisto(rnd_6, "six", 100000)
