import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def plotting(x, y, z):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.plot(x, y, z, label='Auslenkung mit '+str(len(x))+' Schritten')
    ax.legend()
    plt.savefig("build/"+str(len(x))+"Schritten.pdf")
    plt.close()


def auslenkung(x):
    zeit = range(0, len(x))
    plt.plot(zeit, x, label="Auslenkung in x-Richtung")
    plt.xlabel("Zeitschritt")
    plt.ylabel("Auslenkung")
    plt.legend(loc='best')
    plt.savefig("build/zeitauslenk"+str(len(x))+"Schritten.pdf")
    plt.close()


def energieerhaltung(x, y, z, vx, vy, vz):
    ekin = 0.5*vx**2
    epot = 0.5*x**2
    zeit = range(0, len(x))
    plt.plot(zeit, ekin, label="Ekin")
    plt.plot(zeit, epot, label="Epot")
    plt.plot(zeit, epot+ekin, label="Ekin+Epot")
    plt.xlabel("Zeitschritt")
    plt.ylabel("Energie")
    plt.legend(loc='best')
    plt.savefig("build/energieerhaltung"+str(len(x))+"Schritten.pdf")
    plt.close()

if __name__ == '__main__':

    # schritte = [1001, 2001, 3001]
    schritte = [101, 201, 301, 401, 501, 1001, 2001, 3001, 4001, 5001, 102, 202, 302, 402, 502, 1002, 2002, 3002, 4002, 5002, 103, 203, 303, 403, 503, 1003, 2003, 3003, 4003, 5003]
    for schritt in schritte:
        x, y, z, vx, vy, vz = np.genfromtxt('build/auslenkSchritt'+str(schritt)+'.txt',
                                unpack='True')
        plotting(x, y, z)
        auslenkung(x)
        energieerhaltung(x, y, z, vx, vy, vz)

    #v ungleich 0
    x, y, z, vx, vy, vz = np.genfromtxt('build/auslenkSchritt'+str(3000)+'.txt', unpack='True')
    plotting(x, y, z)

    #v ungleich 0
    x, y, z, vx, vy, vz = np.genfromtxt('build/auslenkSchritt'+str(2999)+'.txt', unpack='True')
    plotting(x, y, z)
