import numpy as np
import matplotlib.pyplot as plt


def plotting(T):
    mu = 0
    sigma = np.sqrt(T)
    x_normal_verteilung = np.random.normal(mu, sigma, 100000)
    y_normal_verteilung = np.random.normal(mu, sigma, 100000)
    v_norm= np.sqrt(x_normal_verteilung**2+y_normal_verteilung**2)
    x = np.linspace(0, 10)
    plt.hist(v_norm, 30, normed=True)
    # plt.plot(x, np.sin(x))
    plt.plot(x, (1/(2*np.pi*T))**(3/2)*np.exp(-x**2/(2*T)) )
    # plt.savefig("build/plots/plot.pdf")
    plt.show()



if __name__ == '__main__':
    # H = np.genfromtxt('build/magnetisierung.txt', unpack='True')
    plotting(1)
