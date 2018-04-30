import matplotlib.pyplot as plt
import numpy 

E = numpy.genfromtxt("cElectrico.txt")
V = numpy.genfromtxt("placas.txt")

n = numpy.size(E,1) ; n2 = int(n/2)
Ex = E[:,:n2] ;Ey = E[:,n2:] ; X,Y = numpy.meshgrid(range(n2),range(n2))
plt.figure()
plt.imshow(V,cmap='autumn'); plt.colorbar(); plt.streamplot(X,Y,Ex,Ey, density=2.0, linewidth=0.5,color='k') ;plt.savefig('placas.pdf')
