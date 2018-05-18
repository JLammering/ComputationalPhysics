import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, fmin
import uncertainties.unumpy as unp
import matplotlib.colors as colors


def plotMatrix(matrix, dateiname):

    x = np.arange(0, len(matrix))
    plt.pcolormesh(x, x, matrix)
    plt.colorbar(label='Spin')
    plt.savefig("build/plots/" + dateiname + ".pdf")
    plt.close()


def plotEnergie(schritt, energie, dateiname):
    ''' plottet die Energie'''
    plt.plot(schritt, energie, '.')
    plt.xlabel("sweep")
    plt.ylabel("energie/spin")
    plt.savefig("build/plots/energie"+dateiname+".pdf")
    plt.close()


def plotMagnetisierung(schritt, magnetisierung, dateiname, yachse):
    plt.plot(schritt, magnetisierung, '.')
    plt.xlabel("sweep")
    plt.ylabel(yachse+"/spin")
    plt.savefig("build/plots/"+dateiname+".pdf")
    plt.close()


def plotTempAbhaengig(temperaturen, magnetisierung, dateiname, yachse):
    plt.plot(temperaturen, magnetisierung, '.')
    plt.xlabel("kB*T")
    plt.ylabel(yachse+"/spin")
    plt.savefig("build/plots/"+dateiname+".pdf")
    plt.close()


if __name__ == '__main__':

    endungen =("eins", "zwei", "drei", "eins_sweep", "zwei_sweep", "drei_sweep")
    for i, elem in enumerate(endungen):
        matrix = np.genfromtxt('build/kbTgleich'+elem+'.txt', unpack='True')
        plotMatrix(matrix, 'kbTgleich' + elem)

        if i == 0 or i == 1 or i == 2:  # äquilibrierungsphase
            energie, schritte = np.genfromtxt('build/energiekbTgleich'+elem+'gleich.txt', unpack='True')
            plotEnergie(schritte, energie, 'kbTgleich'+elem+'gleich')

        energie, schritte = np.genfromtxt('build/energiekbTgleich'+elem+'.txt', unpack='True')
        plotEnergie(schritte, energie, 'kbTgleich'+elem)

        magnetisierung, schritte = np.genfromtxt('build/magnetkbTgleich'+elem+'.txt', unpack='True')
        plotMagnetisierung(schritte, magnetisierung, 'magnetkbTgleich'+elem, "<m>")

        absmagnet, schritte = np.genfromtxt('build/absmagnetkbTgleich'+elem+'.txt', unpack='True')
        plotMagnetisierung(schritte, absmagnet, 'absmagnetkbTgleich'+elem, "<|m|>")
        print("plotted"+elem)

    tempmagnet, temperaturen = np.genfromtxt('build/tempmagnetdatei.txt', unpack='True')
    plotTempAbhaengig(temperaturen, tempmagnet, "tempmagnet", "<m>")
    tempmagnet, temperaturen = np.genfromtxt('build/tempabsmagnetdatei.txt', unpack='True')
    plotTempAbhaengig(temperaturen, tempmagnet, "abstempmagnet", "<|m|>")
    spezwaerme, temperaturen = np.genfromtxt('build/tempspezwaermedatei.txt', unpack='True')
    plotTempAbhaengig(temperaturen, spezwaerme, "spezwaerme", "c(T)")
