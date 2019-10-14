CFLAGS=-Wall -pedantic -std=c11 -I. -g                                                                                                                                                                                                                                             
all: queue1 queue2 queue3 queue4 queue5 queue6

%.o: %.c %.h
				gcc ${CFLAGS} -c $<

queue1: queue1.o queue.o
				gcc ${CFLAGS} queue.o queue1.o -o $@

queue2: queue2.o queue.o
				gcc ${CFLAGS} queue.o queue2.o -o $@

queue3: queue3.o queue.o
				gcc ${CFLAGS} queue.o queue3.o -o $@

queue4: queue4.o queue.o
				gcc ${CFLAGS} queue.o queue4.o -o $@

queue5: queue5.o queue.o
				gcc ${CFLAGS} queue.o queue5.o -o $@

queue6: queue6.o queue.o
				gcc ${CFLAGS} queue.o queue6.o -o $@

clean:
				rm -f *.o queue1 queue2 queue3 queue5 queue6
