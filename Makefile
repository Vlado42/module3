CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: test1

hash.o: 			hash.c hash.h queue.h
							gcc $(CFLAGS) -c hash.c

test1.o:			test1.c hash.h queue.h
							gcc $(CFLAGS) -c test1.c

queue.o:			queue.c queue.h
							gcc $(CFLAGS) -c cart2.c

test1:				test1.o hash.o queue.o
							gcc $(CFLAGS) test1.o hash.o queue.o -o cart1

clean:
							rm -f *.o test1

