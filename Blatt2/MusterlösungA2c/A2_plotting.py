import numpy as np
import matplotlib.pyplot as plt


# a)
def f(x):
	return np.cos(x)

bins=np.arange(-np.pi/2, np.pi/2, np.pi/50)
x = np.linspace(-np.pi/2, np.pi/2, 100)
# i)
set = np.genfromtxt('build/A2a_i', unpack=True)
plt.hist(set, bins, normed=True, label="Zufallszahlen")
plt.xlabel(r'$x$')
plt.plot(x, f(x), 'r-', label="Analytische Verteilung")
plt.legend(loc="upper left")
plt.savefig('build/Aufgabe2_a_i.png')
plt.clf()
# ii)
set = np.genfromtxt('build/A2a_ii', unpack=True)
plt.hist(set, bins, normed=True, label=r"Zufallszahlen mit $u\in[-1,1]$")
plt.xlabel(r'$x$')
plt.plot(x, f(x), 'r-', label="Analytische Verteilung")
plt.legend(loc="upper left")
plt.savefig('build/Aufgabe2_a_ii.png')
plt.clf()

# b)
set = np.genfromtxt('build/A2b', unpack=True)

def gaus(x,moment1,moment2):
	return 1/(np.sqrt(2*np.pi*moment2)) * np.exp(-0.5*(x-moment1)**2/moment2)

a=-10
b=15
x = np.linspace(a, b, 100)
mu = 3
variance = 4
plt.hist(set, bins=np.arange(a, b, 0.2), normed=True, label="Zufallszahlen")
plt.xlabel(r'$z$')
plt.plot(x, gaus(x,mu,variance), 'r', label="Analytische Verteilung")
plt.legend(loc="upper left")
plt.savefig('build/Aufgabe2_b.png')
plt.clf()

# c)
def exponential(x):
	return 1/2*np.exp(-abs(x))
a=-5
b=10
x = np.linspace(a, b, 200)
set = np.genfromtxt('build/A2c', unpack=True)
k=1.5
plt.hist(set, bins=np.arange(a, b, (b-a)/200), normed=True, label="Zufallszahlen")
plt.xlabel(r'$y$')
plt.plot(x, gaus(x,mu,1), 'r', label=r"$p(y)$")
plt.plot(x, k*exponential(x-3), 'r', label=r"$k g(y)$")
plt.legend(loc="upper left")
plt.savefig('build/Aufgabe2_c.png')
plt.clf()

# bonus
bins=np.arange(a, b, (b-a)/50)
x = np.linspace(a, b, 100)
set = np.genfromtxt('build/A2c_distribution', unpack=True)
plt.hist(set, bins, normed=True, label=r"Zufallszahlen $y_1$")
plt.xlabel(r'$y$')
plt.plot(x, exponential(x-3), 'r-', label=r"Analytische Verteilung $g(y)$")
plt.legend(loc="upper left")
plt.savefig('build/Aufgabe2_c_distribution.png')
plt.clf()
