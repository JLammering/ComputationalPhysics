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
    plt.plot(schritt, energie)
    plt.xlabel("sweep")
    plt.ylabel("energie")
    plt.savefig("build/plots/energie"+dateiname+".pdf")
    plt.close()

def plotMagnetisierung(schritt, magnetisierung, dateiname, yachse):
    plt.plot(schritt, magnetisierung)
    plt.xlabel("sweep")
    plt.ylabel(yachse)
    plt.savefig("build/plots/"+dateiname+".pdf")
    plt.close()


if __name__ == '__main__':
    # kbT = 1
    # matrix1 = np.genfromtxt('build/kbT=1.txt', unpack='True')
    # plotMatrix(matrix1, 'kbTgleicheins')
    # matrix3 = np.genfromtxt('build/kbT=3.txt', unpack='True')
    # plotMatrix(matrix3, 'kbTgleichdrei')

    endungen =("eins", "zwei", "drei", "eins_sweep", "zwei_sweep", "drei_sweep")
    for i, elem in enumerate(endungen):
        matrix = np.genfromtxt('build/kbTgleich'+elem+'.txt', unpack='True')
        plotMatrix(matrix, 'kbTgleich' + elem)

        energie, schritte = np.genfromtxt('build/energiekbTgleich'+elem+'.txt', unpack='True')
        plotEnergie(schritte, energie, 'kbTgleich'+elem)

        magnetisierung, schritte = np.genfromtxt('build/magnetkbTgleich'+elem+'.txt', unpack='True')
        plotMagnetisierung(schritte, magnetisierung, 'magnetkbTgleich'+elem, "<m>")

        absmagnet, schritte = np.genfromtxt('build/absmagnetkbTgleich'+elem+'.txt', unpack='True')
        plotMagnetisierung(schritte, absmagnet, 'absmagnetkbTgleich'+elem, "<|m|>")
        print("plotted"+elem)

    # energie
    # energie1, schritte1 = np.genfromtxt('build/energiekbTgleicheins.txt', unpack='True')
    # plotEnergie(energie1, schritte1, 'kbTgleicheins')
    #
    #
    # energie2, schritte2 = np.genfromtxt('build/energiekbTgleichzwei.txt', unpack='True')
    # plotEnergie(energie2, schritte2, 'kbTgleichzwei')
    #
    # energie3, schritte3 = np.genfromtxt('build/energiekbTgleichdrei.txt', unpack='True')
    # plotEnergie(energie3, schritte3, 'kbTgleichdrei')
