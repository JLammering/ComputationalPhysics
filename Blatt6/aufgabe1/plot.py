import numpy as np
import matplotlib.pyplot as plt


def plotting(T_eigen, T_lanczos, T_householder):
    N = range(3, 21)
    plt.plot(N, T_eigen, 'kx', label='Zeiten des EigenSolvers')
    plt.plot(N, T_lanczos, 'bx', label='Zeiten von Lanczos + QR-Iteration')
    plt.plot(N, T_householder, 'rx', label='Zeiten von Householder + QR-Iteration')
    plt.xlim(0, 21)
    plt.ylabel('Laufzeit in sek')
    plt.xlabel('Dimension der Matrix')
    plt.legend(loc='best')

    plt.savefig("build/plots/plot.pdf")
    plt.close()


if __name__ == '__main__':
    T_eigen, T_lanczos, T_householder = np.genfromtxt('build/zeiten.txt', unpack='True')
    plotting(T_eigen, T_lanczos, T_householder)
