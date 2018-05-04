import matplotlib.pyplot as plt
import numpy as np

# zufallszahlen importieren
print("lese daten ein ...")
x1 = np.genfromtxt("build/random1.txt", unpack=True)
x2 = np.genfromtxt("build/random2.txt", unpack=True)
print("-daten eingelesen-")
# histogramme erstellen mit mpl
x_plot = np.linspace(0, np.pi/2)
plt.figure(1)
plt.plot(x_plot, np.cos(x_plot), label="Kosinusfunktion")
plt.hist(x1, bins=int(np.sqrt(len(x1))), range=(-2, 2), histtype='bar', normed=True,
         label="Generierte  Zufallszahlen # = 1e5)")
plt.xlabel("bins")
plt.ylabel("# hits (normiert)")
plt.legend(loc='best')
plt.savefig("build/aufgabe2_a_i.pdf")
plt.figure(2)
plt.plot(x_plot, np.cos(x_plot), label="Kosinusfunktion")
plt.hist(x2, bins=int(np.sqrt(len(x2))), range=(-2, 2), histtype='bar', normed=True,
         label="Generierte  Zufallszahlen # = 1e5)")
plt.xlabel("bins")
plt.ylabel("# hits (normiert)")
plt.tight_layout(pad=0, h_pad=1.08, w_pad=1.08)
plt.legend(loc='best')
plt.savefig("build/aufgabe2_a_ii.pdf")
