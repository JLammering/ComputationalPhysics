# import numpy as np
# import matplotlib.pyplot as plt

#
# def plotting():
#     x = np.linspace(0, 10)
#     plt.plot(x, np.sin(x))
#     plt.savefig("build/plots/plot.pdf")
#
#
# if __name__ == '__main__':
#     theta1, theta2, theta1punkt, theta2punkt = np.genfromtxt('build/magnetisierung.txt', unpack='True')
#     plotting()
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys

theta1, theta2, theta1punkt, theta2punkt = np.genfromtxt("build/auslenk1.txt", unpack=True)

theta1_2, theta2_2, theta1punkt_2, theta2punkt_2 = np.genfromtxt("build/auslenk2.txt", unpack=True)

plt.plot(theta1)
plt.plot(theta2)
plt.xlabel=r'$t$'
plt.ylabel=r'$\theta(t)$'
plt.tight_layout(pad=0)
plt.savefig('build/1.pdf')
plt.close()


plt.plot(theta1_2)
plt.plot(theta2_2)
plt.xlabel=r'$t$'
plt.ylabel=r'$\theta(t)$'
plt.tight_layout(pad=0)
plt.savefig('build/2.pdf')
plt.close()

# massen
m_1 = 1
m_2 = 1

# laengen
l_1 = 1
l_2 = 1

g = 9.81

T = 0.5 * m_1 * theta1punkt**2 * l_1**2 + 0.5 * m_2 * (theta2punkt**2 * l_2**2 + theta1punkt**2 * l_1**2 + 2*theta1punkt * l_1 * theta2punkt * l_2 * np.cos(theta2-theta1))

V = -g * (m_1  * l_1 * np.cos(theta1) + m_2 *  l_1 * np.cos(theta1) + m_2 * l_2 * np.cos(theta2))


T2 = 0.5 * m_1 * theta1punkt_2**2 * l_1**2 + 0.5 * m_2 * (theta2punkt_2**2 * l_2**2 + theta1punkt_2**2 * l_1**2 + 2*theta1punkt_2 * l_1 * theta2punkt_2 * l_2 * np.cos(theta2_2-theta1_2))

V2 = -g * (m_1  * l_1 * np.cos(theta1_2) + m_2 *  l_1 * np.cos(theta1_2) + m_2 * l_2 * np.cos(theta2_2))


plt.plot(T + V, label='T + V')
#plt.plot(theta2)
plt.legend(loc='best')
plt.tight_layout(pad=0)
plt.savefig('build/energie.pdf')
plt.close()

plt.plot(T2 + V2, label='T + V')
#plt.plot(theta2)
plt.legend(loc='best')
plt.tight_layout(pad=0)
plt.savefig('build/energie2.pdf')
plt.close()

fig = plt.figure()
ax = plt.subplot(111)

def animat(t):
    print('\r{}'.format(t), end='')
    ax.cla()
    plot = ax.plot((0, l_1*np.sin(theta1[t]), l_1*np.sin(theta1[t]) + l_2*np.sin(theta2[t])), (0, -l_1*np.cos(theta1[t]), -l_1*np.cos(theta1[t])-l_2*np.cos(theta2[t])))
    plt.axis('equal')
    plt.axis([-4, 4, -4, 4])
    ax.set_title('Doppelpendel – Step: {}'.format(t), loc='right')
    return plot

def animat2(t):
    print('\r{}'.format(t), end='')
    ax.cla()
    plot = ax.plot((0, l_1*np.sin(theta1_2[t]), l_1*np.sin(theta1_2[t]) + l_2*np.sin(theta2_2[t])), (0, -l_1*np.cos(theta1_2[t]), -l_1*np.cos(theta1_2[t])-l_2*np.cos(theta2_2[t])))
    plt.axis('equal')
    plt.axis([-4, 4, -4, 4])
    ax.set_title('Doppelpendel – Step: {}'.format(t), loc='right')
    return plot

#writer = animation.ImageMagickWriter(fps=25)
ani = animation.FuncAnimation(fig, animat, frames=int(len(theta1)))

#plt.show()
ani.save('build/anim.mp4', fps=10)
plt.close()

fig = plt.figure()
ax = plt.subplot(111)

def animat2(t):
    print('\r{}'.format(t), end='')
    ax.cla()
    plot = ax.plot((0, l_1*np.sin(theta1_2[t]), l_1*np.sin(theta1_2[t]) + l_2*np.sin(theta2_2[t])), (0, -l_1*np.cos(theta1_2[t]), -l_1*np.cos(theta1_2[t])-l_2*np.cos(theta2_2[t])))
    plt.axis('equal')
    plt.axis([-4, 4, -4, 4])
    ax.set_title('Doppelpendel – Step: {}'.format(t), loc='right')
    return plot
ani2 = animation.FuncAnimation(fig, animat2, frames=int(len(theta1_2)))
ani2.save('build/anim2.mp4', fps=10)
#print()
