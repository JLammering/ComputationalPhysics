import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.cm as cm


# def maxwell2d(vel, tem):
#     t = 0.5 / tem
#     return(2 * t * vel * np.exp(- t * vel**2))
#
#
#if __name__ == '__main__':
# def plotting(T):
#     number = int(1e5)
#     mu = 0
#     sigma = 1
#     x_normal_verteilung = np.random.normal(mu, sigma, number)
#     y_normal_verteilung = np.random.normal(mu, sigma, number)
#     v_norm = np.sqrt(T) * np.sqrt(x_normal_verteilung**2 + y_normal_verteilung**2)
#     x = np.linspace(0, 10, 1e4)
#     plt.hist(v_norm, int(number**(0.333)), normed=True)
#     # plt.plot(x, np.sin(x))
#     # plt.plot(x, (1/(2*np.pi*T))**(3/2)*np.exp(-x**2/(2*T)))
#     plt.plot(x, maxwell2d(x, T))
#     # plt.savefig("build/plots/plot.pdf")
#     plt.show()
#     return()
# darstellung der MD_Simulation
anzahl_steps = 100

fig = plt.figure()

def update_fig(steps):
        #plt.clf()
        fig.clear()
        matrix = np.genfromtxt("build/"+str(steps)+".txt", unpack='True')
        colors = cm.rainbow(np.linspace(0, 1, matrix.shape[0]))
        for i in range(matrix.shape[0]):
            frame = plt.plot(matrix[i, 0], matrix[i, 1], marker='o',  markersize=10, color= colors[i])
        plt.title('sweep nr:' +str(steps))
        # plt.colorbar(label='Spin')
        return(frame)


def MDanime():
    file = open("build/paras.txt", "r")
    anzahl_steps = int(file.readline())
    file.close()

    ax = fig.add_subplot(1, 1, 1)
    ax.set_xlim(0, 8)
    ani1 = animation.FuncAnimation(fig, update_fig, frames=anzahl_steps)
    ani1.save('md_sim.mp4', fps=2)
    plt.show()

if __name__ == '__main__':
    # plotting(1)
    MDanime()
