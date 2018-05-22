import numpy as np
import matplotlib.pyplot as plt


def plotting():
    x = np.linspace(0, 10)
    plt.plot(x, np.sin(x))
    plt.savefig("build/plots/plot.pdf")


if __name__ == '__main__':
    # H = np.genfromtxt('build/magnetisierung.txt', unpack='True')
    plotting()
