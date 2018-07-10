import numpy as np
import matplotlib.pyplot as plt

def maxwell2d(vel, tem):
    t = 0.5 / tem
    return(2 * t * vel * np.exp(- t * vel**2))


def plotting(T):
    number = 1e5
    mu = 0
    sigma = 1
    x_normal_verteilung = np.random.normal(mu, sigma, number)
    y_normal_verteilung = np.random.normal(mu, sigma, number)
    v_norm = np.sqrt(T) * np.sqrt(x_normal_verteilung**2 + y_normal_verteilung**2)
    x = np.linspace(0, 10, 1e4)
    plt.hist(v_norm, int(number**(0.333)), normed=True)
    # plt.plot(x, np.sin(x))
    plt.plot(x, (1/(2*np.pi*T))**(3/2)*np.exp(-x**2/(2*T)) )
    plt.plot(x, maxwell2d(x, T))
    # plt.savefig("build/plots/plot.pdf")
    plt.show()



if __name__ == '__main__':
    # H = np.genfromtxt('build/magnetisierung.txt', unpack='True')
    plotting(1)
