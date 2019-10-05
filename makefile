all : langtonsAnt

langtonsAnt: main.o langtonsant.o
	g++ main.o langtonsant.o -o langtonsAnt

main.o: main.cpp
	g++ -c main.cpp

langtonsant.o: langtonsant.cpp
	g++ -c langtonsant.cpp

clean: 
	rm *o langtonsAnt

