import matplotlib.pyplot as plt
import numpy as np

# zufallszahlen importieren
print("lese daten ein ...")
x1 = np.genfromtxt("build/gauss.txt", unpack=True)

# parameter gaussfunc
mu = 3.0
si = 2.0


# gaussfunktion
def g(x, m, s):
    vorfakt = 1.0 / np.sqrt(2 * np.pi * s**2)
    exponen = - (x - m)**2 / (2 * si**2)
    return(vorfakt * np.e**exponen)

print("-daten eingelesen-")

rg = 40 # range des histogramms
# histogramme erstellen mit mpl
plt.figure(1)
x_plot = np.linspace(-rg, rg, 1e5)
plt.hist(x1, bins=int(np.sqrt(len(x1))), range=(-rg, rg), histtype='bar',
         normed=True,
         label="Generierte  Zufallszahlen # = 1e6)")

plt.plot(x_plot, g(x_plot, mu, si),
         label=r'$\mathrm{gaussfunktion \ mit } \ \mu = 3 \ \mathrm{und} \ \sigma = 2$')
plt.xlabel("bins")
plt.ylabel("# hits (normiert)")
plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
plt.legend(loc='best')
plt.savefig("build/aufgabe2_b.pdf")
