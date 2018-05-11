caos.pdf:caos.py datos.txt output.txt
	python caos.py

datos.txt: output.txt
	tail -n +5 output.txt > datos.txt

output.txt: caos.x
	./caos.x > output.txt

caos.x: caos.cpp
	c++ caos.cpp -o caos.x

