import matplotlib.pyplot as plt
import numpy as np


def plotMagnetisierung(magnetisierung, H):
    plt.plot(H, magnetisierung, 'rx', label='numerisch')
    plt.plot(H, np.tanh(H), 'b-', label=r'$\tanh\left( \beta H \right)$')
    plt.xlabel('H')
    plt.ylabel('m(H)')
    plt.legend(loc='best')
    plt.savefig("build/magnetisierung.pdf")
    plt.close()


if __name__ == '__main__':
    magnetisierung, H = np.genfromtxt('build/magnetisierung.txt', unpack='True')


plotMagnetisierung(magnetisierung, H)  # rufe plotfunktion auf
