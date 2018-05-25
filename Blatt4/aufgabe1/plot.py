import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


def plotMatrix(matrix, dateiname):

    x = np.arange(0, len(matrix))
    plt.pcolormesh(x, x, matrix)
    plt.colorbar(label='Spin')
    plt.savefig("build/plots/" + dateiname + ".pdf")
    plt.close()

if __name__ == '__main__':


    anzahl_steps = 100
    # for i in range(anzahl_steps):
    #     mat = np.genfromtxt("build/2DTESTRUN"+str(i)+".txt", unpack='True')
    #     plotMatrix(mat, "2DTESTRUN"+str(i))


def update_fig1(steps):
        steps *= 1
        matrix = np.genfromtxt("build/2ZUSTAENDE_RUN"+str(steps)+".txt", unpack='True')
        x = np.arange(0, len(matrix))
        frame = plt.pcolormesh(x, x, matrix)
        plt.title('sweep nr:' +str(steps))
        # plt.colorbar(label='Spin')
        return(frame)

def update_fig2(steps):
        steps *= 1
        matrix = np.genfromtxt("build/3ZUSTAENDE_RUN"+str(steps)+".txt", unpack='True')
        x = np.arange(0, len(matrix))
        frame = plt.pcolormesh(x, x, matrix)
        plt.title('sweep nr:' + str(steps))
        # plt.colorbar(label='Spin')
        return(frame)


ani1 = animation.FuncAnimation(plt.figure(), update_fig1, frames=anzahl_steps)
plt.show()
ani2 = animation.FuncAnimation(plt.figure(), update_fig2, frames=anzahl_steps)
plt.show()
