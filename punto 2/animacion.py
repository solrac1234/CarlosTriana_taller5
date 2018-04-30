import numpy as np
from matplotlib.pyplot import figure, plot, ylim, cla, subplots
import matplotlib.animation as animation
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt

fig = plt.figure()
cuerda = np.genfromtxt("cuerda.txt", delimiter=" ", skip_header=0, skip_footer=0, unpack=False)
x = np.linspace(0,1000,np.size(cuerda,1))

def animar(i):
	cla()
	plot(x,cuerda[i,:],lw=2)
	ylim(ymax=100)
	ylim(ymin=-100)


    
fig,ax = subplots()
anim = animation.FuncAnimation(fig, animar, frames=np.size(cuerda,0))
anim.save('cuerda.gif', writer='imagemagick', fps=np.size(cuerda,0)/2)
