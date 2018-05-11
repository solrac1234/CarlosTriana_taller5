import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt



try:
	
	q2,p2 = genfromtxt("output.txt", unpack=True)
	plt.ylabel('p2');plt.xlabel('q2');plt.plot(q2,p2, 'o-')
	plt.savefig('caos1.pdf')

except Exception as error:
	print("error\n\n",error)


try:
	
	q1,q2,p1,p2 = genfromtxt("datos.txt", unpack=True)

	
	A,B,C,D,E= 2,1,2,3,4
	f=0.001;xlims = [0,600];H=len(q1)
	plt.figure(figsize=(12,12));plt.subplot(A,A,B);plt.plot(q1[:f*H]);plt.xlabel('I');plt.ylabel('q1')
	

	plt.subplot(A,A,C);plt.plot(q2[:f*H]);plt.xlabel('I');plt.ylabel('q2')
	plt.subplot(A,A,D);plt.plot(p1[:f*H]);plt.xlabel('I');plt.ylabel('p1')
	plt.subplot(A,A,E);plt.plot(p2[:f*H]);plt.xlabel('I');plt.ylabel('p2')
	plt.savefig('caos.pdf')

except Exception as error:
	print("Problemas con los datos\n\n",error)
