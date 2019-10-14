CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: queue1 queue2 queue3

%.o: %.c %.h
			gcc ${CFLAGS} -c $<

queue1: queue1.o queue.o
				gcc ${CFLAGS} queue.o queue1.o -o $@

queue2: queue2.o queue.o
				gcc ${CFLAGS} queue.o queue2.o -o $@

queue3: queue3.o queue.o
				gcc ${CFLAGS} queue.o queue3.o -o $@

clean:
				rm -f *.o queue1 queue2 queue3
