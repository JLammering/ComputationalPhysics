import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, fmin
import uncertainties.unumpy as unp
import matplotlib.colors as colors


def plotHistoScatter(rnd, dateiname, m):

    # Histogramm erstellen
    plt.hist(rnd, bins=10)
    plt.xlabel(r'$bin$')
    plt.ylabel(r'$Häufigkeit$')
    plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
    plt.savefig("build/"+dateiname+"Hist.pdf")
    plt.close()

    # Datenpaare plotten
    # rnd[:min(m, 100000)-1] geht vom ersten bis zum vorletzten
    # rnd[1:min(m, 100000)] geht vom zweiten bis zum letzten
    plt.scatter(rnd[:min(m, 100000)-1], rnd[1:min(m, 100000)])
    plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
    plt.savefig("build/"+dateiname+"Scatter.pdf")
    plt.close()


def plotRekursion(periode):
    # Farbplot erstellen um Periode der b,c Kombi zun untersuchen
    x = np.arange(0.5, 16.5)  # dafür sorgen, dass die Zahlen in der Mitte der Kästchen sind
    plt.pcolormesh(x, x, periode,
                   norm=colors.LogNorm())  # beide Koordinaten, dann periode
    # logarithmische Farbskala sorgt für bessere Lesbarkeit
    plt.colorbar(label='Periode')
    plt.xlabel('b')
    plt.ylabel('c')
    plt.savefig("build/rekursionstest.pdf")
    plt.close()


if __name__ == '__main__':
    # LCG
    rnd_1 = np.genfromtxt('build/ersterGenerator.txt', unpack='True')
    plotHistoScatter(rnd_1, "erster", 6075)

    rnd_2 = np.genfromtxt('build/zweiterGenerator.txt', unpack='True')
    plotHistoScatter(rnd_2, "zweiter", 256)

    rnd_3 = np.genfromtxt('build/dritterGenerator.txt', unpack='True')
    plotHistoScatter(rnd_3, "dritter", 2147483648)

    rnd_4 = np.genfromtxt('build/vierterGenerator.txt', unpack='True')
    plotHistoScatter(rnd_4, "vierter", 2147483647)

    # XORshift
    rnd_5 = np.genfromtxt('build/fifthGenerator.txt', unpack='True')
    plotHistoScatter(rnd_5, "fifth", 100000)

    rnd_6 = np.genfromtxt('build/sixGenerator.txt', unpack='True')
    plotHistoScatter(rnd_6, "six", 100000)

    # Periode untersuchen
    periode = np.genfromtxt('build/Rekursionstest.txt', unpack='True')
    plotRekursion(periode)
