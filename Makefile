CC = gcc
CCFLAGS = -Wall
EXE = test_fetch_store

all: $(EXE)

cpu.o: cpu.h cpu.c
	$(CC) $(CCFLAGS) -c cpu.c

test_fetch_store.o: test_fetch_store.c cpu.o
	$(CC) $(CCFLAGS) -c test_fetch_store.c

test_fetch_store: test_fetch_store.o
	$(CC) -o test_fetch_store test_fetch_store.o cpu.o

clean:
	rm -rf *.o $(EXE)

new:
	make clean
	make all

.PHONY: all clean new
