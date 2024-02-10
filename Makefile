CC = gcc

simplewc: simplewc.o
	${CC} simplewc.o -o simplewc

simplewc.o: simplewc.c functions.h tests/tests.h
	${CC} -c simplewc.c

clean:
	rm *.o simplewc
