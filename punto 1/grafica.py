import numpy as np
import matplotlib.pyplot as plt

V = np.genfromtxt("placas.txt")
E = np.genfromtxt("cElectrico.txt")

Ex = E[:,:(int(np.size(E,1)/2))]
Ey = E[:,(int(np.size(E,1)/2)):]
x,y = np.meshgrid(range(int(np.size(E,1)/2)),range(int(np.size(E,1)/2)))

plt.imshow(V,cmap='seismic'); plt.colorbar()
plt.streamplot(x,y,Ex,Ey, density=2.0, linewidth=0.5,color='k')
plt.savefig('placas.pdf')
