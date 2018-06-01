import numpy as np
import matplotlib.pyplot as plt


def plotting(eigenwerte, dateiname):

    nummer = range(1, len(eigenwerte)+1)
    eigenwerte.sort()
    plt.plot(nummer, eigenwerte, 'kx', label="eigenwerte "+dateiname)
    plt.legend(loc='best')
    plt.xlabel("# Eigenwert")
    plt.ylabel("Eigenwert")
    plt.savefig("build/plots/"+dateiname+".pdf")
    plt.close()


if __name__ == '__main__':
    eigenwertePH = np.genfromtxt('build/perHand.txt', unpack='True')
    plotting(eigenwertePH, "perHand")

    eigenwerteES = np.genfromtxt('build/mitEigensolver.txt', unpack='True')
    plotting(eigenwerteES, "mitEigensolver")
