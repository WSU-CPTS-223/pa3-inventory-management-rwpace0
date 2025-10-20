out: clean run execute

compile: main.cpp
	g++ -g -Wall -std=c++14 main.cpp Inventory.cpp -o mainexe

run: mainexe
	./mainexe

runnew:
	g++ -g -Wall -std=c++14 main.cpp Inventory.cpp -o mainexe && ./mainexe

clean:
	rm -f mainexe