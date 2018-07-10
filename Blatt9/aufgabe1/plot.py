import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


def maxwell2d(vel, tem):
    t = 0.5 / tem
    return(2 * t * vel * np.exp(- t * vel**2))


def plotting(T):
    number = int(1e5)
    mu = 0
    sigma = 1
    x_normal_verteilung = np.random.normal(mu, sigma, number)
    y_normal_verteilung = np.random.normal(mu, sigma, number)
    v_norm = np.sqrt(T) * np.sqrt(x_normal_verteilung**2 + y_normal_verteilung**2)
    x = np.linspace(0, 10, 1e4)
    plt.hist(v_norm, int(number**(0.333)), normed=True)
    # plt.plot(x, np.sin(x))
    # plt.plot(x, (1/(2*np.pi*T))**(3/2)*np.exp(-x**2/(2*T)))
    plt.plot(x, maxwell2d(x, T))
    # plt.savefig("build/plots/plot.pdf")
    plt.show()


# darstellung der MD_Simulation
anzahl_steps = 200
def update_fig(steps):
        steps *= 1
        matrix = np.genfromtxt("build/"+str(steps)+".txt", unpack='True')
        frame = plt.plot(matrix[:,0], matrix[:,1], '.', marker='o',  markersize=10)
        #x = np.arange(0, len(matrix))
        #frame = plt.pcolormesh(x, x, matrix)
        plt.title('sweep nr:' +str(steps))
        # plt.colorbar(label='Spin')
        return(frame)

ani1 = animation.FuncAnimation(plt.figure(), update_fig, frames=anzahl_steps)
plt.show()


if __name__ == '__main__':
    # H = np.genfromtxt('build/magnetisierung.txt', unpack='True')
    plotting(1)
