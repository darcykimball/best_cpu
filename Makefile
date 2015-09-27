CC = gcc
CCFLAGS = -Wall
EXES = test_fetch_store test_arithmetic test_pq procsim

all: $(EXES)

cpu.o: cpu.h cpu.c
	$(CC) $(CCFLAGS) -c cpu.c

test_fetch_store.o: test_fetch_store.c cpu.o
	$(CC) $(CCFLAGS) -c test_fetch_store.c

test_arithmetic.o: test_arithmetic.c cpu.o
	$(CC) $(CCFLAGS) -c test_arithmetic.c

test_fetch_store: test_fetch_store.o
	$(CC) -o test_fetch_store test_fetch_store.o cpu.o

test_arithmetic: test_arithmetic.o
	$(CC) -o test_arithmetic test_arithmetic.o cpu.o

test_pq: test_pq.o pqueue.o
	$(CC) -o test_pq test_pq.o pqueue.o

procsim: procsim.o pqueue.o cpu.o proctab.h
	$(CC) -o procsim procsim.o pqueue.o cpu.o

pqueue.o: pqueue.h pqueue.c
	$(CC) $(CCFLAGS) -c pqueue.c

test_pq.o: test_pq.c pqueue.o test.h
	$(CC) $(CCFLAGS) -c test_pq.c

procsim.o: procsim.c
	$(CC) $(CCFLAGS) -c procsim.c

clean:
	rm -rf *.o $(EXES)

new:
	make clean
	make all

.PHONY: all clean new
