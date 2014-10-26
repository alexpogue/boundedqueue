all: app test

app: main.o BoundedQueue.o
	g++ -o bq main.o BoundedQueue.o
test: test.o BoundedQueue.o
	g++ -o test test.o BoundedQueue.o

main.o: main.cpp BoundedQueue.h
	g++ -c main.cpp
test.o: test.cpp QUnit.hpp
	g++ -c test.cpp
BoundedQueue.o: BoundedQueue.cpp BoundedQueue.h
	g++ -c BoundedQueue.cpp

clean:
	rm *.o

tar:
	tar -cvf queue.tar *.cpp *.hpp *.h README.txt makefile
