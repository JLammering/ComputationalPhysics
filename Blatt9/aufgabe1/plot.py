import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.cm as cm


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
    return()
# darstellung der MD_Simulation


def plotmessungen():
    time, geschwindigkeit = np.genfromtxt("build/measurements.txt", unpack='True')

    plt.plot(time, geschwindigkeit, label='geschwindigkeit')
    plt.xlabel('time/s')
    plt.legend(loc='best')
    plt.savefig('build/messung.pdf')


def MDanime_fancy():
    file = open("build/paras.txt", "r")
    para = []
    for val in file.read().split():
        para.append(int(val))
    anzahl_steps = para[0]
    abstand = para[1]
    file.close()
    fig = plt.figure(facecolor='black', figsize=(16,9))
    ax = plt.subplot(1, 1, 1)
    #step = 0
    colors = cm.rainbow(np.linspace(0, 1, 16))
    plot, = ax.plot(np.zeros(16), np.zeros(16), 'o', markersize=6)
    ax.set_xlim(0, 8)
    ax.set_ylim(0, 8)
    plt.axis('off')
    plt.tight_layout(pad=0)

    def update(frame):
        matrix = np.genfromtxt("build/"+str(frame)+".txt", unpack='True')

        plot.set_xdata(matrix[:,0])
        plot.set_ydata(matrix[:,1])
        return plot,

    def init():
        return update(1)

    ani1 = animation.FuncAnimation(fig, update, frames=range(abstand, anzahl_steps, abstand), interval=20, init_func=init, blit=True)
    ani1.save('build/md_sim.mp4', fps=25, savefig_kwargs={'facecolor':'black'}, dpi = 120)
    #plt.show()

def MDanime():
    file = open("build/paras.txt", "r")
    para = []
    for val in file.read().split():
        para.append(int(val))
    anzahl_steps = para[0]
    abstand = para[1]
    file.close()
    fig = plt.figure()
    #step = 0
    colors = cm.rainbow(np.linspace(0, 1, 16))

    def update(frame):
        plt.clf()
        plt.xlim(0, 8)
        plt.ylim(0, 8)
        #fig.clear()
        matrix = np.genfromtxt("build/"+str(frame)+".txt", unpack='True')
        #print(xdata)
        plt.plot(frame, np.sin(frame))
        for i in range(matrix.shape[0]):
           plt.plot(matrix[i, 0], matrix[i, 1], marker='o',  markersize=10, color= colors[i])
        plt.title('Zeitschritt nr:' +str(frame))

    ani1 = animation.FuncAnimation(fig, update, frames=range(abstand, anzahl_steps, abstand), interval=20)
    ani1.save('build/md_sim.mp4', fps=20)
    plt.show()

if __name__ == '__main__':
    # plotting(1)
    MDanime_fancy()
    plotmessungen()
