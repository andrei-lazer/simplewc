simplewc: simplewc.o
	g++ simplewc.o -o simplewc

simplewc.o: simplewc.c functions.h tests/tests.h
	g++ -c simplewc.c

clean:
	rm *.o simplewc
