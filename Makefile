CFLAGS = -g -Wall
 # -fprofile-arcs -ftest-coverage

all: test

test.o: test.c
	gcc $(CFLAGS) -c test.c
graph.o: graph.c
	gcc $(CFLAGS) -c graph.c
test: test.o graph.o
	gcc $(CFLAGS) graph.o test.o -o test

clean: 
	rm -rf *.o test